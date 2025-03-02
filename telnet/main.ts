import { TesiraNet } from './telnet.ts';

const tesira = new TesiraNet({
  host: '169.254.3.243',
  port: 23,
  negotiationMandatory: false,
  timeout: 5000,
  localAddress: '169.254.3.240',
});

tesira.on('connected', () => console.log('connected to tesira'));

Deno.serve(
  {
    port: 53533,
    hostname: '127.0.0.1',
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
