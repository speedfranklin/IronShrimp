
Database files: https://stackoverflow.com/a/77500/3285968

pg_dump -U postgres --schema-only ironshrimp > creationScript.sql

Set PGUSER ENV variable
Make pg.conf file at %APP_DATA%/postgresql/pgpass.conf with:

*:5432:[db_name]:postgres:[mypassword]
Open terminal, use "psql" to launch with defaults assuming environment variables are set: pg_env.bat

C:\Users\SpeedFranklin\source\IronShrimp\Data\2015_9_28_opiate_Cal\Opiate_Cal_1_BK.datx
C:\Users\SpeedFranklin\source\IronShrimp\Data\2015_9_28_opiate_Cal\ExportedPeakList.xls

C:\Users\SpeedFranklin\source\IronShrimp\Data\2017_10_27_Opiate_water_1\2017_10_27_Opiate_water_1_Scan1_is1.datx
