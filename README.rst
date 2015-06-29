

.. -*- mode: rst -*-

Setup
-----
* Setup athena ::

  setupATLAS
  asetup AthAnalysisBase 2.3.11, here 
   

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

rootStreamName = "TauEmbdValHistoStream"
rootFileName   = "TauEmbdValHists.root"
embdvalalg.RootStreamName   = rootStreamName
embdvalalg.RootDirName      = "/Hists"

Run
--- 

* To sumbit the JObOption::
athena TauEmbdValJoboptions.py



