
.. -*- mode: rst -*-

Setup
-----
  * in the directory containing TauEmbdVal package do::
  setupATLAS
  asetup, here 
   
Input
----
* To specify the input xAOD files ::
in the TauEmbdValJobOptions.py set the file path

* To set the EventLoop size::
set the theApp.EvtMax = <the number of events that you are intersted in>

Output
_____

* To set the output stream and to save the output histograms in a root file, 
change the fllowing lines ::
svcMgr.THistSvc.Output += ["TauEmbdVal DATAFILE='Test01.root' OPT='RECREATE'"]

Run
--- 

* To sumbit the JObOption::
athena TauEmbdValJoboptions.py



