/**
 * Options for creating a new TCP connection.
 */
export type TelnetOptions = {
  /** Host the client should connect to. Defaults to '127.0.0.1'. */
  host?: string;
  /** Port the client should connect to. Defaults to '23'. */
  port?: number;
  /** Local interface to bind for network connections. Defaults to an empty string. */
  localAddress?: string;
  /** Allows to pass an object, which can contain every property from Node's SocketConnectOpts. Defaults to an empty object. */
  socketConnectOptions?: object;
  /** Sets the socket to timeout after the specified number of milliseconds of inactivity on the socket. */
  timeout?: number;
  /** Shell prompt that the host is using. Can be a string or an instance of RegExp. Defaults to regex /(?:\/ )?#\s/. */
  shellPrompt?: string | RegExp;
  /** Username/login prompt that the host is using. Can be a string or an instance of RegExp. Defaults to regex /login[: ]*$/i. */
  loginPrompt?: string | RegExp;
  /** Password/login prompt that the host is using. Can be a string or an instance of RegExp. Defaults to regex /Password: /i. */
  passwordPrompt?: string | RegExp;
  /** String or regex to match if your host provides login failure messages. Defaults to undefined. */
  failedLoginMatch?: string | RegExp;
  /** Flag used to determine if an initial 0x03 (CTRL+C) should be sent when connected to server. */
  initialCtrlC?: boolean;
  /** Flag used to determine if an initial '\r\n' (CR+LF) should be sent when connected to server. */
  initialLFCR?: boolean;
  /** Username used to login. Defaults to 'root'. */
  username?: string;
  /** Password used to login. Defaults to 'guest'. */
  password?: string;
  /** Duplex stream which can be used for connection hopping/reusing. */
  sock?: any;
  /** Input record separator. A separator used to distinguish between lines of the response. Defaults to '\r\n'. */
  irs?: string;
  /** Output record separator. A separator used to execute commands (break lines on input). Defaults to '\n'. */
  ors?: string;
  /** The number of lines used to cut off the response. Defaults to 1. With a value of 0, no lines are cut off. */
  echoLines?: number;
  /** Whether shell prompt should be excluded from the results. Defaults to true. */
  stripShellPrompt?: boolean;
  /** The pattern used (and removed from final output) for breaking the number of lines on output. Defaults to '---- More'. */
  pageSeparator?: string;
  /** Disable telnet negotiations if needed. Can be used with 'send' when telnet specification is not needed. Defaults to true. */
  negotiationMandatory?: boolean;
  /** A timeout used to wait for a server reply when the 'exec' method is used. Defaults to 2000 (ms). */
  execTimeout?: number;
  /** A timeout used to wait for a server reply when the 'send' method is used. Defaults to 2000 (ms). */
  sendTimeout?: number;
  /** Maximum buffer length in bytes which can be filled with response data. Defaults to 1M. */
  maxBufferLength?: number;
  /** When set to non-zero values, telnet-client will respond to the host command IAC DO 0x18 (Terminal Type) with IAC WILL 0x18, and it will respond to IAC DO 0x1F with the given terminal width and height. */
  terminalWidth?: number;
  terminalHeight?: number;
  /** If provided, incoming line breaks will be normalized to the provided character/string of characters. */
  newlineReplace?: string;
  /** An optional function that receives escape sequences from the host. The function can either return null, which means to take no action, or a string value to be sent to the host as a response. */
  escapeHandler?: (sequence: string) => string | null;
  /** If set to true, escape sequences and control characters (except for \t, \n, and \r) will be stripped from incoming data. escapeHandler is not affected. */
  stripControls?: boolean;
  /** The maximum time, in milliseconds, to wait for a callback from socket.end(…) after calling end(). Defaults to 250 milliseconds. */
  maxEndWait?: number;
  /** The telnet protocol is designed mainly for 7-bit ASCII characters, and a default encoding used is 'ascii'. You can attempt to use other encodings, however, such as 'utf8' and 'latin1'. */
  encoding?: string;
  /** If set to true, the library will not try to login into to the host automatically. This is set to false by default. */
  disableLogon?: boolean;
};
