export X509_USER_PROXY=$PWD/proxy.pem
voms-proxy-init -out proxy.pem

server=https://cmsweb.cern.ch/dqm/online/data/browse/Original

dir=00014xxxx/0001464xx
file=DQM_V0001_Info_R000146428.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000146430.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000146431.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000146436.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000146437.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000146442.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001465xx
file=DQM_V0001_Info_R000146510.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000146511.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000146513.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000146514.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000146589.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001466xx
file=DQM_V0001_Info_R000146644.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000146698.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001467xx
file=DQM_V0001_Info_R000146703.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000146710.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000146712.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000146713.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000146715.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000146719.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000146721.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000146724.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000146728.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000146729.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001468xx
file=DQM_V0001_Info_R000146804.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000146806.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000146807.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001469xx
file=DQM_V0001_Info_R000146944.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001470xx
file=DQM_V0001_Info_R000147043.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000147048.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001471xx
file=DQM_V0001_Info_R000147114.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000147115.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000147116.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000147196.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001472xx
file=DQM_V0001_Info_R000147206.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000147212.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000147214.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000147216.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000147217.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000147218.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000147219.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000147221.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000147222.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000147284.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001473xx
file=DQM_V0001_Info_R000147390.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001474xx
file=DQM_V0001_Info_R000147450.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000147451.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000147452.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000147453.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000147454.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001477xx
file=DQM_V0001_Info_R000147749.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000147752.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000147753.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000147754.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000147755.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000147757.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001479xx
file=DQM_V0001_Info_R000147926.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000147927.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000147929.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001480xx
file=DQM_V0001_Info_R000148002.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000148029.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000148031.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000148032.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000148057.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000148058.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001488xx
file=DQM_V0001_Info_R000148819.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000148822.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000148828.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000148829.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000148844.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000148859.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000148860.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000148862.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000148864.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001489xx
file=DQM_V0001_Info_R000148952.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000148953.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001490xx
file=DQM_V0001_Info_R000149003.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000149011.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000149058.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000149063.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000149064.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001491xx
file=DQM_V0001_Info_R000149181.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000149182.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001492xx
file=DQM_V0001_Info_R000149291.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000149294.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001494xx
file=DQM_V0001_Info_R000149442.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
