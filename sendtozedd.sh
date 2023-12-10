echo "Sending project to zeddboard"
zip -r attention.zip attention
scp attention.zip mts247@zhang-zedboard-11.ece.cornell.edu:~
rm attention.zip