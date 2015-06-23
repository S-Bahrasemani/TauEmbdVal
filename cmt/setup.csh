# echo "setup TauEmbdVal TauEmbdVal-00-00-00 in /cluster/warehouse/sbahrase/TauEmbeddingValidation"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/atlas.cern.ch/repo/sw/software/AthAnalysisBase/x86_64-slc6-gcc48-opt/2.3.11/CMT/v1r25p20140131
endif
source ${CMTROOT}/mgr/setup.csh
set cmtTauEmbdValtempfile=`${CMTROOT}/${CMTBIN}/cmt.exe -quiet build temporary_name`
if $status != 0 then
  set cmtTauEmbdValtempfile=/tmp/cmt.$$
endif
${CMTROOT}/${CMTBIN}/cmt.exe setup -csh -pack=TauEmbdVal -version=TauEmbdVal-00-00-00 -path=/cluster/warehouse/sbahrase/TauEmbeddingValidation  -no_cleanup $* >${cmtTauEmbdValtempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/${CMTBIN}/cmt.exe setup -csh -pack=TauEmbdVal -version=TauEmbdVal-00-00-00 -path=/cluster/warehouse/sbahrase/TauEmbeddingValidation  -no_cleanup $* >${cmtTauEmbdValtempfile}"
  set cmtsetupstatus=2
  /bin/rm -f ${cmtTauEmbdValtempfile}
  unset cmtTauEmbdValtempfile
  exit $cmtsetupstatus
endif
set cmtsetupstatus=0
source ${cmtTauEmbdValtempfile}
if ( $status != 0 ) then
  set cmtsetupstatus=2
endif
/bin/rm -f ${cmtTauEmbdValtempfile}
unset cmtTauEmbdValtempfile
exit $cmtsetupstatus

