import { z, ZodType } from 'npm:zod';
import { TesiranetConfig } from './tesira.ts';
import { Func } from './util/types.ts';

// ---------------------------------------------------

export const CMD_RECEIVE = {
  /** attempt connection to tesira. new connections should restart the telnet connection. */
  tesira_connect: z.object({
    remoteAddress: z.string(),
    localAddress: z.string(),
  } satisfies Record<keyof TesiranetConfig, ZodType>),

  /** RUN a tesira command. */
  tesira_run: z.object({
    message: z.string(),
  }),
} satisfies Record<string, ZodType>;

export type CMD_SEND = {
  /** report a change in connection status */
  tesira_connect_status: {
    connected: boolean;
  };
};

// ---------------------------------------------------

export function getHandleFunction(obj: any) {
  const handle = <T extends keyof typeof CMD_RECEIVE>(
    type: T,
    cb: Func<[z.infer<(typeof CMD_RECEIVE)[T]>], void>
  ) => {
    if (type !== obj.type) return;
    const val = CMD_RECEIVE[type];

    const { success, data } = val.safeParse(obj.data);
    if (!success) return;

    cb(data);
  };

  return handle;
}
