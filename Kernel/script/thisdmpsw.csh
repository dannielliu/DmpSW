#! /bin/tcsh
#+
#+  $Id: thisdmpsw.csh, 2014-04-27 10:51:41 DAMPE $
#+  Author(s):
#+    Chi WANG (chiwang@mail.ustc.edu.cn) 01/10/2013
#+-----------------------------------------------------------------------
#+   source me(anywhere is Okay) to setup envirenment of DAMPE software
#+-----------------------------------------------------------------------
#+

#+  Set installation environment of DAMPE offline software 

if ( ! ($?DMPSWSYS) ) then
  set thisDmpSW="`dirname $0`/.."
  setenv DMPSWSYS "`cd ${thisDmpSW};pwd`"
  unset thisDmpSW
  setenv DMPSWWORK "$HOME/dmpwork"
  setenv PATH $DMPSWSYS/bin:$PATH
  setenv PYTHONPATH $DMPSWSYS/lib:$DMPSWWORK/lib:$PYTHONPATH
  if ( ($?LD_LIBRARY_PATH) ) then
    setenv LD_LIBRARY_PATH $DMPSWSYS/lib:$DMPSWWORK/lib:$LD_LIBRARY_PATH
  else if ( ($?DYLD_LIBRARY_PATH) ) then        # Mac OS
    setenv DYLD_LIBRARY_PATH $DMPSWSYS/lib:$DMPSWWORK/lib:$DYLD_LIBRARY_PATH
  endif
endif

