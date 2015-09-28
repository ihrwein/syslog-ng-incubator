if ENABLE_RUST

export top_srcdir
export top_builddir
export rust_modules_libdir

lib_LIBRARIES = modules/rust/libsyslog-ng-rust-deps.a
modules_rust_libsyslog_ng_rust_deps_a_SOURCES = \
  modules/rust/rust-grammar.y       \
  modules/rust/rust-parser.c        \
  modules/rust/rust-parser.h        \
  modules/rust/filter.c               \
  modules/rust/filter.h				\
  modules/rust/parser.c				\
  modules/rust/parser.h

modules_rust_libsyslog_ng_rust_deps_a_CPPFLAGS = \
  $(INCUBATOR_CFLAGS)	-fPIC		\
  $(SYSLOG_NG_RUST_MODULES_CFLAGS)			\
  -I$(top_srcdir)/modules/rust        \
  -I$(top_builddir)/modules/rust

#modules_rust_librust_la_LIBADD = $(SYSLOG_NG_RUST_MODULES_LIBS) $(INCUBATOR_LIBS)
modules_rust_libsyslog_ng_rust_deps_a_LDFLAGS = -avoid-version -module -no-undefined -R ${rust_modules_libdir}

else
modules/rust modules/rust/ mod-rust: modules/rust/librust.la
endif

BUILT_SOURCES       +=      \
  modules/rust/rust-grammar.y       \
  modules/rust/rust-grammar.c       \
  modules/rust/rust-grammar.h

EXTRA_DIST        +=      \
  modules/rust/rust-grammar.ym

.PHONY: modules/rust/ mod-rust

