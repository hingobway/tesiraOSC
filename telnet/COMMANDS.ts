import { z, ZodType } from 'npm:zod';
import { TesiranetConfig } from './tesira.ts';

// ---------------------------------------------------

export const CMD_RECEIVE = {
  /** attempt connection to tesira. new connections should restart the telnet connection. */
  tesira_connect: z.object({
    remoteAddress: z.string(),
    localAddress: z.string(),
    port: z.number(),
  } satisfies Record<keyof TesiranetConfig, ZodType>),

  /** RUN a tesira command. */
  tesira_run: z.object({
    message: z.string(),
  }),
} satisfies Record<string, ZodType>;

// ---------------------------------------------------

export type CMD_SEND = {
  /** report a change in connection status */
  tesira_connect_status: {
    connected: boolean;
  };
};
