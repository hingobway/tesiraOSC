import { CMD_SEND } from './COMMANDS.ts';
import { Func } from './util/types.ts';

export class Sockets {
  private sockets: WebSocket[] = [];
  private listeners: [keyof WebSocketEventMap, Func][] = [];

  addSocket(ws: WebSocket) {
    this.sockets.push(ws);

    // register existing listeners
    for (const [t, cb] of this.listeners) {
      ws.addEventListener(t, cb);
    }

    // remove on close
    ws.addEventListener('close', () => {
      const index = this.sockets.indexOf(ws);
      if (index !== -1) {
        this.sockets.splice(index, 1);
      }
    });
  }

  send<K extends keyof CMD_SEND>(type: K, data: CMD_SEND[K]) {
    const msg = JSON.stringify({ type, data });
    for (const ws of this.sockets) {
      ws.send(msg);
    }
  }

  listen<T extends keyof WebSocketEventMap>(
    type: T,
    listener: (this: WebSocket, ev: WebSocketEventMap[T]) => unknown
  ) {
    this.listeners.push([type, listener]);
    for (const s of this.sockets) {
      s.addEventListener(type, listener);
    }
  }

  unlisten<T extends keyof WebSocketEventMap>(
    type: T,
    listener: (this: WebSocket, ev: WebSocketEventMap[T]) => unknown
  ) {
    for (const ws of this.sockets) {
      ws.removeEventListener(type, listener);
    }
  }
}
