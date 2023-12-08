echo "Sending project to zeddboard"
zip -r GEMM.zip GEMM
scp GEMM.zip mts247@zhang-zedboard-11.ece.cornell.edu:~
rm GEMM.zip