export X509_USER_PROXY=$PWD/proxy.pem
voms-proxy-init -out proxy.pem

server=https://cmsweb.cern.ch/dqm/online/data/browse/Original

dir=00013xxxx/0001324xx 
file=DQM_V0001_Info_R000132440.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132442.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132471.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132473.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132474.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132476.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132477.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132478.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001325xx
file=DQM_V0001_Info_R000132569.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132572.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132573.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132596.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132597.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132598.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132599.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001326xx
file=DQM_V0001_Info_R000132601.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132602.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132605.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132606.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132646.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132647.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132648.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132650.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132652.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132653.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132654.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132656.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132658.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132659.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132661.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132662.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001327xx
file=DQM_V0001_Info_R000132716.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001329xx
file=DQM_V0001_Info_R000132958.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132959.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132960.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132961.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132965.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000132968.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001330xx
file=DQM_V0001_Info_R000133029.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133030.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133031.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133034.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133035.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133036.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133038.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133046.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133081.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133082.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001331xx
file=DQM_V0001_Info_R000133146.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133147.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133158.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133161.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133172.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001332xx
file=DQM_V0001_Info_R000133239.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133241.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133242.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133248.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133250.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133257.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133269.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133270.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133280.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133289.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001333xx
file=DQM_V0001_Info_R000133320.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133321.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133324.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133336.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001334xx
file=DQM_V0001_Info_R000133446.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133448.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133450.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133463.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133472.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133474.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133483.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001335xx
file=DQM_V0001_Info_R000133509.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133510.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133511.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001338xx
file=DQM_V0001_Info_R000133874.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133875.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133876.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133877.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133881.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133885.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001339xx
file=DQM_V0001_Info_R000133927.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000133928.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001347xx
file=DQM_V0001_Info_R000134721.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000134725.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001350xx
file=DQM_V0001_Info_R000135059.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001351xx
file=DQM_V0001_Info_R000135175.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001355xx
file=DQM_V0001_Info_R000135521.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000135523.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000135525.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000135528.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000135534.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000135535.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000135537.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000135538.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000135573.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000135575.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001357xx
file=DQM_V0001_Info_R000135735.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
