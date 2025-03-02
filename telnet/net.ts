const BUFFER_SIZE = 1024;

const c = await Deno.connect({
  hostname: '127.0.0.1',
  port: 53533,
  transport: 'tcp',
});

const encoder = new TextEncoder();
const decoder = new TextDecoder();

while (true) {
  const buf = new Uint8Array(BUFFER_SIZE);

  await c.read(buf);

  console.log('RECEIVED: ', decoder.decode(buf));
  c.write(encoder.encode('ts message!'));
}
