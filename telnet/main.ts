import { TesiraNet } from './telnet.ts';

// GET ARGS
const PORT_IPC = parseInt(Deno.args[0]);
if (!Number.isFinite(PORT_IPC)) console.error('MISSING IPC PORT');

// TODO wait for IPC command to start this
const tesira = new TesiraNet({
  host: '127.0.0.1',
  // host: '169.254.3.243',
  // localAddress: '169.254.3.240',
  port: 23,
  negotiationMandatory: false,
  timeout: 5000,
});

tesira.on('connected', () => console.log('connected to tesira'));

Deno.serve(
  {
    port: PORT_IPC,
  },
  (req) => {
    if (req.headers.get('upgrade') != 'websocket')
      return new Response(null, { status: 501 });

    const { socket, response } = Deno.upgradeWebSocket(req);

    socket.addEventListener('open', () => {
      console.log('new connection!');
    });

    socket.addEventListener('message', async (e) => {
      // run telnet
      console.log('attempting telnet message ', e.data);

      try {
        await tesira.sendMessage(e.data);
        socket.send('TELNET SUCCESS');
        console.log('success!');
      } catch (_) {
        console.log('FAILED');
      }
    });

    return response;
  }
);
