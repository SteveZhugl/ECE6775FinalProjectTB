echo "Sending project to zeddboard"
zip -r zedboard_proj.zip lab4
scp lab4.zip mts247@zhang-zedboard-11.ece.cornell.edu:~
rm lab4.zip
echo "bitstream to zeddboard"
scp xillydemo.bit mts247@zhang-zedboard-11.ece.cornell.edu:~