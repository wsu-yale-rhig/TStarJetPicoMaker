#!/bin/csh

### to do: find a way to extract 'n' from the xml file

# used to resubmit failed jobs through star-submit
#
# arguments:
# 1: trigsetup (  example: "AuAu_200_production_mid_2014" )
# 2: triggerset ID ( example: 1, 2, etc... defined in the MakeTStarJetPico.cxx macro )
# 3: day number ( example: 91-100 )
# 4: session ID ( example: 409098CFA54082034B0605C36512C954 )
# 5: number of jobs to check ( from 1 -> n )

if ( $# != "5" ) then
        echo 'Error: illegal number of parameters'
        exit
endif

set trigset = $1
set trigid  = $2
set day = $3
set session = $4
set events = $5
set xml = ${session}.session.xml

set outFile = ${YOUROUTPUTSPACE}/y14_production/${trigset}/out/trigger_set_${trigid}/${day}/

if !( -e ${outFile} ) then
    echo 'Are luminosity and day range specified correctly?'
    echo 'Directory not found: '
    echo $outFile
    echo 'exiting'
    exit
endif

@ i = 1
while ( $i <= $events )
    set file = ${outFile}/${session}_${i}.root
    if !( -e ${file}  ) then
	echo Output not found for job ID $i - resubmitting
	star-submit -r $i $xml
    endif
    @ i = $i + 1
end
