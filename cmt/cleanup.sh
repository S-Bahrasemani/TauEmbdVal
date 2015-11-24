# echo "cleanup TauEmbdVal TauEmbdVal-00-00-00 in /home/sbahrase/WorkDesk/TauEmbedding"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc48-opt/20.1.2/CMT/v1r25p20140131; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtTauEmbdValtempfile=`${CMTROOT}/${CMTBIN}/cmt.exe -quiet build temporary_name`
if test ! $? = 0 ; then cmtTauEmbdValtempfile=/tmp/cmt.$$; fi
${CMTROOT}/${CMTBIN}/cmt.exe cleanup -sh -pack=TauEmbdVal -version=TauEmbdVal-00-00-00 -path=/home/sbahrase/WorkDesk/TauEmbedding  $* >${cmtTauEmbdValtempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/${CMTBIN}/cmt.exe cleanup -sh -pack=TauEmbdVal -version=TauEmbdVal-00-00-00 -path=/home/sbahrase/WorkDesk/TauEmbedding  $* >${cmtTauEmbdValtempfile}"
  cmtcleanupstatus=2
  /bin/rm -f ${cmtTauEmbdValtempfile}
  unset cmtTauEmbdValtempfile
  return $cmtcleanupstatus
fi
cmtcleanupstatus=0
. ${cmtTauEmbdValtempfile}
if test $? != 0 ; then
  cmtcleanupstatus=2
fi
/bin/rm -f ${cmtTauEmbdValtempfile}
unset cmtTauEmbdValtempfile
return $cmtcleanupstatus

