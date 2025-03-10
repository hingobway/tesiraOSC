import type { Buffer } from 'node:buffer';
import { EventEmitter } from 'node:events';

import { Telnet } from 'npm:telnet-client';

import { TelnetOptions } from './util/telnetTypes.ts';
import { FAKE_TELNET } from './util/dev.ts';

const ENDLINE = '\r\n';

export type TesiraEventMap = {
  connected: [];
  disconnect: [];
  message: [msg: string];
};

export class TesiraNet extends EventEmitter<TesiraEventMap> {
  connected = false;
  private options: TelnetOptions;
  private telnet: Telnet;

  constructor(options: TelnetOptions) {
    super();
    this.options = options;

    this.telnet = new Telnet();

    this.telnet.on('close', () => {
      this.connected = false;
      this.emit('disconnect');
    });
  }

  async sendMessage(msg: string) {
    if (!this.connected) return false;

    if (FAKE_TELNET) {
      console.log('FAKE SENT', msg);
      return;
    }

    await this.telnet.send(msg);
    const resp = await this.telnet.nextData();
    console.log('RESPONSE RESPONSE: ', resp);
    // await this.waitForResponse('+OK');
  }

  async connect() {
    if (FAKE_TELNET) {
      setTimeout(() => {
        this.connected = true;
        this.emit('connected');
      }, 1000);
      return;
    }

    try {
      console.log('telnet connecting...');
      await this.telnet.connect(this.options);

      let buffer = '';

      this.telnet.on('data', (data: Buffer) => {
        const message = data.toString();

        if (!this.connected) {
          if (!message.includes(ENDLINE)) return;
          this.connected = true;
          this.emit('connected');
          return;
        }

        buffer += message;
        if (buffer.endsWith(ENDLINE)) {
          // HANDLE MESSAGE

          console.log('MESSAGE RECEIVED:', buffer);

          this.emit('message', buffer);

          buffer = '';
        }
      });
    } catch (error) {
      console.log('[TEL] FAILED', (error as any)?.message);
    }
  }

  async close() {
    await this.telnet.end();
  }

  waitForResponse(response: string) {
    return new Promise<void>((resolve) => {
      let buffer = '';

      const handler = (data: Buffer) => {
        const message = data.toString();

        buffer += message;
        if (!buffer.endsWith(ENDLINE)) return;

        buffer.replace(ENDLINE, '');

        if (response.trim() !== buffer.trim()) return;

        this.telnet.removeListener('data', handler);
        resolve();

        buffer = '';
      };

      this.telnet.on('data', handler);
    });
  }
}

export class TesiraWrapper extends EventEmitter<TesiraEventMap> {
  private tesira: TesiraNet;
  private config: TesiranetConfig | null = null;

  constructor() {
    super();
    this.tesira = new TesiraNet({});
  }

  private setup() {
    if (!this.config) return;

    this.tesira = new TesiraNet({
      host: this.config.remoteAddress,
      localAddress: this.config.localAddress,
      port: 23,
      negotiationMandatory: false,
      timeout: 5000,
    });

    this.tesira.connect();

    this.tesira.on('connected', () => {
      this.emit('connected');
    });
    this.tesira.on('disconnect', () => {
      this.emit('disconnect');
      this.setup();
    });
  }

  startup(config: TesiranetConfig) {
    this.config = config;
    this.setup();
  }

  sendMessage(msg: string) {
    this.tesira.sendMessage(msg);
  }
}

export type TesiranetConfig = {
  remoteAddress: string;
  localAddress: string;
};
