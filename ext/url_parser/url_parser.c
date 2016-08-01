#include <ruby.h>
#include "url_parser.h"

/*
static VALUE host_type (enum host_type type)
{
  VALUE htype;
  switch (type)
  {
    case REGNAME:
      htype = rb_to_symbol (rb_str_new2 ("REGNAME"));
      break;
    case IPV4ADDR:
      htype = rb_to_symbol (rb_str_new2 ("IPV4ADDR"));
      break;
    case IPV6ADDR:
      htype = rb_to_symbol (rb_str_new2 ("IPV6ADDR"));
      break;
    case IPVFUTUR:
      htype = rb_to_symbol (rb_str_new2 ("IPVFUTUR"));
      break;
    default:
      htype = rb_to_symbol (rb_str_new2 ("UNKNOWN"));
      break;
  }
  return htype;
}
*/

static VALUE url_parser_initialize (VALUE self, VALUE url_str)
{
  URL *url = url_create();
  rb_iv_set (self, "@url_str", url_str);
  if (!url_parse (RSTRING_PTR(url_str), url))
  {
    rb_iv_set (self, "@valid", Qfalse);
    return self;
  }

  if (url->host->type == UNKNOWN)
  {
    rb_iv_set (self, "@valid", Qfalse);
    return self;
  }
  rb_iv_set (self, "@valid", Qtrue);
  rb_iv_set (self, "@scheme", rb_str_new2 (url->scheme));
  rb_iv_set (self, "@userinfo", url->userinfo ? rb_str_new2 (url->userinfo) : Qnil);
  rb_iv_set (self, "@hosttype", host_type(url->host->type));

  url_free (url);

  return self;
}

static VALUE url_parser_to_s (VALUE self)
{
  return rb_iv_get(self, "@url_str");
}

static VALUE url_parser_scheme (VALUE self)
{
  return rb_iv_get(self, "@scheme");
}

void Init_url_parser (void)
{
  VALUE mUrlParser = rb_define_module ("UrlParser");
  VALUE cUrlParser = rb_define_class_under (mUrlParser, "URL", rb_cObject);

  rb_define_method (cUrlParser, "initialize", url_parser_initialize, 1);
  rb_define_method (cUrlParser, "to_s", url_parser_to_s, 0);
  rb_define_method (cUrlParser, "scheme", url_parser_scheme, 0);
}
