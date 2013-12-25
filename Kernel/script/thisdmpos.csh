#! /bin/tcsh
#=====================================================================
#   File:   thisdmpos.csh
#   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    01/10/2013
#---------------------------------------------------------------------
#   Description:
#       source thie file:
#       1)  cd /prefix
#       2)  source ./bin/thisdmpos.(c)sh
#
#---------------------------------------------------------------------
#   History:
#                           Last update:  14/12/2013   10:50:56
#=====================================================================

#+  Set installation environment of DAMPE offline software 

if ( ! ($?DMPOSSYS) ) then
  setenv DMPOSSYS `(pwd)`
  setenv PATH $DMPOSSYS/bin:$PATH
  if ( ($?LD_LIBRARY_PATH) ) then
    setenv LD_LIBRARY_PATH $DMPOSSYS/lib:$LD_LIBRARY_PATH
  else if ( ($?DYLD_LIBRARY_PATH) ) then        # Mac OS
    setenv DYLD_LIBRARY_PATH $DMPOSSYS/lib:$DYLD_LIBRARY_PATH
  endif
endif
