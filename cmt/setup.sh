# echo "setup TauEmbdVal TauEmbdVal-00-00-00 in /cluster/warehouse/sbahrase/TauEmbeddingValidation"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/atlas.cern.ch/repo/sw/software/AthAnalysisBase/x86_64-slc6-gcc48-opt/2.3.11/CMT/v1r25p20140131; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtTauEmbdValtempfile=`${CMTROOT}/${CMTBIN}/cmt.exe -quiet build temporary_name`
if test ! $? = 0 ; then cmtTauEmbdValtempfile=/tmp/cmt.$$; fi
${CMTROOT}/${CMTBIN}/cmt.exe setup -sh -pack=TauEmbdVal -version=TauEmbdVal-00-00-00 -path=/cluster/warehouse/sbahrase/TauEmbeddingValidation  -no_cleanup $* >${cmtTauEmbdValtempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/${CMTBIN}/cmt.exe setup -sh -pack=TauEmbdVal -version=TauEmbdVal-00-00-00 -path=/cluster/warehouse/sbahrase/TauEmbeddingValidation  -no_cleanup $* >${cmtTauEmbdValtempfile}"
  cmtsetupstatus=2
  /bin/rm -f ${cmtTauEmbdValtempfile}
  unset cmtTauEmbdValtempfile
  return $cmtsetupstatus
fi
cmtsetupstatus=0
. ${cmtTauEmbdValtempfile}
if test $? != 0 ; then
  cmtsetupstatus=2
fi
/bin/rm -f ${cmtTauEmbdValtempfile}
unset cmtTauEmbdValtempfile
return $cmtsetupstatus

