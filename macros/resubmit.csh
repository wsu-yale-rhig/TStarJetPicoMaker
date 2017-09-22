#!/bin/csh

### to do: find a way to extract 'n' from the xml file

# used to resubmit failed jobs through star-submit
#
# arguments:
# 1: trigsetup (  example: "AuAu_200_production_mid_2014" )
# 2: day number ( example: 91-100 )
# 3: session ID ( example: 409098CFA54082034B0605C36512C954 )
# 4: number of jobs to check ( from 1 -> n )

if ( $# != "4" ) then
        echo 'Error: illegal number of parameters'
        exit
endif

set trigset = $1
set day = $2
set session = $3
set events = $4
set xml = ${session}.session.xml

set outFile = ${NSCRATCH}/y14_production/${trigset}/out/${day}/

if !( -e ${outFile} ) then
    echo 'Are luminosity and day range specified correctly?'
    echo 'Directory not found: '
    echo $outFile
    echo 'exiting'
    exit
endif

@ i = 1
while ( $i <= $events )
    set file = ${outFile}/AuAu14Pico_${session}_${i}.root
    if !( -e ${file}  ) then
	echo Output not found for job ID $i - resubmitting
	star-submit -r $i $xml
    endif
    @ i = $i + 1
end
