#include <ruby.h>
#include "url_parser.h"

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
  rb_iv_set (self, "@host", url->host->name ? rb_str_new2 (url->host->name) : Qnil);
  rb_iv_set (self, "@host_type", host_type(url->host->type));
  rb_iv_set (self, "@port", url->port ? UINT2NUM(url->port) : Qnil);
  rb_iv_set (self, "@path", url->path ? rb_str_new2 (url->path) : Qnil);
  rb_iv_set (self, "@query", url->query ? rb_str_new2 (url->query) : Qnil);
  rb_iv_set (self, "@fragment", url->fragment ? rb_str_new2 (url->fragment) : Qnil);

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

static VALUE url_parser_valid (VALUE self)
{
  return rb_iv_get(self, "@valid");
}

static VALUE url_parser_userinfo (VALUE self)
{
  return rb_iv_get(self, "@userinfo");
}

static VALUE url_parser_host (VALUE self)
{
  return rb_iv_get(self, "@host");
}

static VALUE url_parser_host_type (VALUE self)
{
  return rb_iv_get(self, "@host_type");
}

static VALUE url_parser_port (VALUE self)
{
  return rb_iv_get(self, "@port");
}

static VALUE url_parser_path (VALUE self)
{
  return rb_iv_get(self, "@path");
}

static VALUE url_parser_query (VALUE self)
{
  return rb_iv_get(self, "@query");
}

static VALUE url_parser_fragment (VALUE self)
{
  return rb_iv_get(self, "@fragment");
}

void Init_url_parser(void)
{
  VALUE mUrlParser = rb_define_module ("UrlParser");
  VALUE cUrlParser = rb_define_class_under (mUrlParser, "URL", rb_cObject);

  rb_define_method (cUrlParser, "initialize", url_parser_initialize, 1);
  rb_define_method (cUrlParser, "to_s", url_parser_to_s, 0);
  rb_define_method (cUrlParser, "valid?", url_parser_valid, 0);
  rb_define_method (cUrlParser, "scheme", url_parser_scheme, 0);
  rb_define_method (cUrlParser, "userinfo", url_parser_userinfo, 0);
  rb_define_method (cUrlParser, "host", url_parser_host, 0);
  rb_define_method (cUrlParser, "host_type", url_parser_host_type, 0);
  rb_define_method (cUrlParser, "port", url_parser_port, 0);
  rb_define_method (cUrlParser, "path", url_parser_path, 0);
  rb_define_method (cUrlParser, "query", url_parser_query, 0);
  rb_define_method (cUrlParser, "fragment", url_parser_fragment, 0);
}
