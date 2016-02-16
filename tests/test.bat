REM
replace.exe
IF NOT ERRORLEVEL 1 GOTO err

REM
replace.exe qqut output.txt pa papa
IF NOT ERRORLEVEL 1 GOTO err

REM
replace.exe input.txt output.txt pa papa
IF ERRORLEVEL 1 GOTO err
FC /b output.txt toutputs/toutput.txt
IF ERRORLEVEL 1 GOTO err

REM
replace.exe input.txt output1.txt 12345 !
IF ERRORLEVEL 1 GOTO err
FC /b output1.txt toutputs/toutput1.txt
IF ERRORLEVEL 1 GOTO err

REM
replace.exe input.txt output2.txt "" papa
IF ERRORLEVEL 1 GOTO err
FC /b output2.txt toutputs/toutput2.txt
IF ERRORLEVEL 1 GOTO er

ECHO Program testing succeeded :-) 
EXIT
  
:err
ECHO Program testing failed :-( 
EXIT