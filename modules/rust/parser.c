#include "parser.h"
#include "rust-parser-proxy.h"

typedef struct _ParserRust {
  LogParser super;
  struct RustParserProxy* rust_object;
} ParserRust;

static LogPipe*
rust_parser_clone(LogPipe *s);

gboolean
rust_parser_process(LogParser *s, LogMessage **pmsg, const LogPathOptions *path_options, const gchar *input, gsize input_len)
{
  ParserRust *self = (ParserRust *) s;

  LogMessage *writable_msg = log_msg_make_writable(pmsg, path_options);
  return rust_parser_proxy_process(self->rust_object, writable_msg, input, input_len);
}

void
rust_parser_set_option(LogParser *s, gchar* key, gchar* value)
{    
  ParserRust *self = (ParserRust *)s;

  rust_parser_proxy_set_option(self->rust_object, key, value);
}

gboolean
rust_parser_init(LogPipe *s)
{
  ParserRust *self = (ParserRust *) s;

  return !!rust_parser_proxy_init(self->rust_object);
}

static void
rust_parser_free(LogPipe *s)
{
  ParserRust *self = (ParserRust *)s;

  rust_parser_proxy_free(self->rust_object);
  log_parser_free_method(s);
}

static void
__setup_callback_methods(ParserRust *self)
{
  self->super.process = rust_parser_process;
  self->super.super.free_fn = rust_parser_free;
  self->super.super.clone = rust_parser_clone;
  self->super.super.init = rust_parser_init;
}

static LogPipe*
rust_parser_clone(LogPipe *s)
{
  ParserRust *self = (ParserRust*) s;
  ParserRust *cloned;
  
  cloned = (ParserRust*) g_new0(ParserRust, 1);
  log_parser_init_instance(&cloned->super, s->cfg);
  cloned->rust_object = rust_parser_proxy_clone(self->rust_object);

  if (!cloned->rust_object)
    return NULL;

  __setup_callback_methods(cloned);
  
  return &cloned->super.super; 
}

LogParser*
rust_parser_new(GlobalConfig *cfg)
{
  ParserRust *self = (ParserRust*) g_new0(ParserRust, 1);

  log_parser_init_instance(&self->super, cfg);
  self->rust_object = rust_parser_proxy_new(&self->super);

  if (!self->rust_object)
    return NULL;

  __setup_callback_methods(self);

  return &self->super;
}
