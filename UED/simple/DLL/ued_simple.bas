
Attribute VB_name = "UED_simple"
' This assigns the name of the module

' This module requires the dll file UED_simple.dll.
' Put the UED_simple.dll in a place accessable to the MicroSoft compiler
' or Microsoft product (Excel) that will use this module dll.
' (I.e. in \Windows\system32 (For Windows XP ).
' I would recommend using a hard link to the DLL file.  
	fsutil hardlink create "C:\Windows\system32\UED_simple.dll" "C:\Program Files\CS_Suite_4\UED\simple\DLL\UED_simple.dll"

' Or put the DLL in the same directory as the run time program (I.e. in the same directory as the excel spreadsheet that will use the DLL).


' You can instead use the Excel menu "Tools/References" to specify the location of the .DLL
'   (This doesn't always work. If you get an error, use the accessable directory method).

' To use this dll in Excel:
' - In Excel, press Alt-F11 to start the Visual Basic for applications IDE.
' - Select the menu "File/Import file"
' - In the "Import file" requestor, select the .BAS program that matches the DLL.
'    This will add a module to your project's "Modules" list.
'    Note that the module name matches the VB_name attribute specified in the .BAS file.
'
' Note that UED provides a set of standard variable and units codes.
' You may find it useful to also import the file UED_codes.bas
'  (note that at this time this file only lists a few of the units codes

Option Explicit

Declare Function UED_simple_open  Lib "UED_simple.dll" (ByVal UED_filename As String) as Long
' The C function actually returns an unsigned long.  (V.B. does not have this type only Long).
' This returned long is the UED database handle.
' Returns 0 if the open fails.
' This function must be called to open the database.

Declare Function UED_simple_close Lib "UED_simple.dll" (ByVal UED_database_handle as Long) as Long
' Usually returns 0 indicating the database close successfully.
' Any other value can be assumed an error.
' Currently no error codes are enumerated.
' This function must be called to close the database.

Declare Function UED_set_geolocation Lib "UED_simple.dll"(ByVal UED_database_handle as Long,ByVal latitude_dec_deg   as Single,ByVal longitude_dec_deg  as Single,ByVal elevation_m        as Single,ByVal screening_height_m as Single,ByVal station_ID_code    as String) as Long
'   This function adds the specified geolocation parameters to the UED database file.
'   The Geolocation record is optional in the UED database file;
'   but it is strongly recommended to provide these geolocation parameter.
'   If the geolocation record exists, it will be updated with with the parameter
'   values passed to this function.
'   Otherwise the geolocation record will be created and added to the UED file.
'   The station_ID_code parameter is optional pass a null pointer 0 if
'   there is no station ID.


Declare Function UED_simple_get_earliest_date_time Lib "UED_simple.dll" (ByVal UED_database_handle as Long) as double
Declare Function UED_simple_get_latest_date_time Lib "UED_simple.dll" (ByVal UED_database_handle as Long) as double
' Returns the earliest and latest time stamp encountered in the database
' The integer part of the returned double is the year and day of year.
' I.e.  2003001 is Jan 1, 2003.
' The fraction part of the returned double is the time.
'
'   0 is midnight
'   1 second after midnight is 1/86400
'
'   1:00am is 1/24


Declare Function UED_simple_get_for_date Lib "UED_simple.dll" (ByVal UED_database_handle as Long, ByVal date32 as Long, ByVal variable_code as Long, ByRef units_code as Long,ByRef quality as Long, ByRef status as Long) as Single
' Returns the the value for the specified variable on the specified date in the specified units.
' It also returns the quality of the data and the status of the value.
' You should always check the quality of the data returned.

Declare Function UED_simple_get_for_date_short Lib "UED_simple.dll" (ByVal UED_database_handle as Long, ByVal date32 as Long, ByVal variable_code as Long, ByVal units_code as Long) as Single

Declare Function UED_simple_get_last_units   Lib "UED_simple.dll"  as Long
Declare Function UED_simple_get_last_quality Lib "UED_simple.dll"  as Long
Declare Function UED_simple_get_last_status  Lib "UED_simple.dll"  as Long

Declare Function UED_simple_set_for_date Lib "UED_simple.dll" (ByVal UED_database_handle as Long,ByVal value as Single, ByVal date32 as Long, ByVal variable_code as Long,ByVal  units_code as Long,ByVal quality as Long) as Single
' Sets the specified value for the specified date for the specified variable code,
' with the specified units, and data quality.
'
' This function returns the the value for the specified variable on the specified date in the specified units.
' Use the functions UED_simple_get_last_units(), UED_simple_get_last_quality() and UED_simple_get_last_status()
' to check the actual units and quality stored and the status.

'
' The data may actually be stored in the database in different units
' (Depending how values were previously stored) in this case the
' return value will be the actual value stored and the units
' passed in the units_code parameter will be updated to indicate the
' units actually stored. (Generally it is not necessary to check the
' units and returned variable after calling this function unless you
' want to confirm the conversion was done correctly).
'
' You should specify the quality of the data (0 indicate real data).
' there may be a quality check (I.e. a check of valid range of input value)
' Generall the quality will be the same as the passed value, but
' the quality will be updated if the value is out of range.
' If a data value already exists in the database the database will only
' be updated if the specified value has a better quality than the value
' already in the data base (an existing value of the same quality will be
' replaced by the specified value)..
' The value actually stored in the database (and its quality) will be returned,
' so although, generally the returned value will be the same as the passed value,
' the returned value will be different if there is a units conversion, or
' the value in the database is of better quality.
'
' The following notes apply to all  UED_simple_get_XXXX() and UED_simple_set_XXXX() methods:
'
' UED_database_handle is the database handle (obtained when the database is openned with UED_simple_open).
' date is the date to retrieve
' variable code is the UED variable code of the data to retrieve.
' units code is the desired units the value is to be returned in.
' quality is the quality of the data that is returned
' 0 indicates the data is real measured data,
' any quality < 128 is indicates usable data (see below)
' any quality >= 128 is an an erroneous value (see below)
' status indicates if the data was returned successfully
'    0 indicates no error
'    any other value should be assumed as an error (the error codes currently are not enumerated).

' The quality codes are
' Hex Dec  Description
'  0h   0  measured/real
'  1h   1  estimated/calculated  (from real)
'  2h   2  forecasted/simulated  (from real)
'  3h   3  generated             (from real)
'  4h   4  reserver (for future use)
' 05h   5  estimated/calculated from estimated/calculated
' 06h   6  forecasted/simulated from estimated/calculated
' 07h   7  generated            from estimated/calculated
' 08h   8  reserved
' 09h   9  estimated/calculated from forecasted/simulated
' 0Ah  10  forecasted/simulated from forecasted/simulated
' 0Bh  11  generated            from forecasted/simulated
' 0Ch  12  reserved
' 0Dh  13  estimated/calculated from generated
' 0Eh  14  forecasted/simulated from generated
' 0Fh  15  generated            from generated
'
' 40h  64  (reserved - This value is used for internal processing)
'
' 80h 128  not valid
' 81h 129  out of range
' 82h 130  missing
' BFh 191  unknown quality (presumed erroneous)

