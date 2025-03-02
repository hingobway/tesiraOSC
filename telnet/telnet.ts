import type { Buffer } from 'node:buffer';
import { EventEmitter } from 'node:events';

import { Telnet } from 'npm:telnet-client';

import { TelnetOptions } from './util/telnetTypes.ts';

const ENDLINE = '\r\n';

const telnet = new Telnet();

export type TesiraEventMap = {
  connected: [];
  disconnect: [];
  message: [msg: string];
};

export class TesiraNet extends EventEmitter<TesiraEventMap> {
  connected = false;
  options: TelnetOptions;

  constructor(options: TelnetOptions) {
    super();
    this.options = options;

    this.connect();

    telnet.on('close', () => {
      this.connected = false;
      this.emit('disconnect');
    });
  }

  async sendMessage(msg: string) {
    if (!this.connected) return false;
    console.log('FAKE SEND', msg);
    telnet.send(msg);
    await this.waitForResponse('+OK');
  }

  async connect() {
    // while (!this.connected) {
    try {
      console.log('telnet connecting...');
      await telnet.connect(this.options);

      let buffer = '';

      telnet.on('data', (data: Buffer) => {
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
      console.log('FAILED', error);
    }
    // }
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

        telnet.removeListener('data', handler);
        resolve();

        buffer = '';
      };

      telnet.on('data', handler);
    });
  }
}
