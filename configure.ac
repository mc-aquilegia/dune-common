# -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.62])
DUNE_AC_INIT # gets module version from dune.module file
AC_CONFIG_SRCDIR([dune/common/stdstreams.cc])
AC_CONFIG_HEADERS([config.h])

# add configure flags needed to create log files for dune-autobuild
DUNE_AUTOBUILD_FLAGS
# check all dune dependecies and prerequisits
DUNE_CHECK_ALL

# preset variable to path such that #include <dune/...> works
AC_SUBST([DUNE_COMMON_ROOT], '$(abs_top_srcdir)')
AC_SUBST([DUNE_COMMON_BIN], '$(abs_top_srcdir)/bin/')
AC_SUBST([AM_CPPFLAGS], '-I$(top_srcdir)')
AC_SUBST([AM_LDFLAGS], '$(DUNE_LDFLAGS)')
AC_SUBST([LDADD], '$(top_builddir)/lib/libdunecommon.la')

# write output
AC_CONFIG_FILES([Makefile
     lib/Makefile
     bin/Makefile
     cmake/Makefile
     cmake/modules/Makefile
     cmake/scripts/Makefile
     cmake/pkg/Makefile
     dune/Makefile
     dune/common/Makefile
     dune/common/test/Makefile
     dune/common/parallel/Makefile
     dune/common/parallel/test/Makefile
     dune/common/std/Makefile
     doc/Makefile
     doc/comm/Makefile
     doc/comm/figures/Makefile
     doc/doxygen/Makefile
     doc/doxygen/Doxyfile
     doc/buildsystem/Makefile
     m4/Makefile
     am/Makefile
     share/Makefile
     share/bash-completion/Makefile
     share/bash-completion/completions/Makefile
     dune-common.pc])
# make scripts executable
AC_CONFIG_FILES([
     bin/check-log-store],[
     chmod +x bin/check-log-store])
AC_OUTPUT

# print results
DUNE_SUMMARY_ALL
