import { Sockets } from './sockets.ts';
import { TesiraWrapper } from './tesira.ts';
import { getHandleFunction } from './util/ipcHandler.ts';

export class Routing {
  tesira: TesiraWrapper;
  ipc: Sockets;
  constructor(tesira: TesiraWrapper, ipc: Sockets) {
    this.tesira = tesira;
    this.ipc = ipc;
  }

  // IPC HANDLERS

  IPCHandlers(obj: any) {
    const handle = getHandleFunction(obj);

    handle('tesira_connect', (config) => {
      this.tesira.startup(config);
    });

    handle('tesira_run', ({ message }) => {
      this.tesira.sendMessage(message);
    });
  }

  // TESIRA HANDLERS

  TesiraHandlers() {
    this.tesira.on('connected', () => {
      this.ipc.send('tesira_connect_status', { connected: true });
    });

    this.tesira.on('disconnect', () => {
      this.ipc.send('tesira_connect_status', { connected: false });
    });
  }
}
