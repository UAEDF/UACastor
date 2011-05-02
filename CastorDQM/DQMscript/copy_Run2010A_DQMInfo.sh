export X509_USER_PROXY=$PWD/proxy.pem
voms-proxy-init -out proxy.pem

server=https://cmsweb.cern.ch/dqm/online/data/browse/Original

dir=00013xxxx/0001360xx
file=DQM_V0001_Info_R000136033.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000136035.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000136066.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000136080.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000136082.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000136087.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000136088.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000136097.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000136098.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001361xx
file=DQM_V0001_Info_R000136100.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000136119.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001362xx
file=DQM_V0001_Info_R000136290.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000136294.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000136297.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001370xx
file=DQM_V0001_Info_R000137027.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000137028.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001385xx
file=DQM_V0001_Info_R000138560.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000138562.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000138563.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000138564.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000138565.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000138570.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000138571.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000138572.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001387xx
file=DQM_V0001_Info_R000138737.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000138738.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000138739.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000138742.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000138744.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000138745.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000138746.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000138747.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000138749.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000138750.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000138751.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001389xx
file=DQM_V0001_Info_R000138919.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000138920.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000138921.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000138923.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000138924.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000138937.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000138939.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001390xx
file=DQM_V0001_Info_R000139020.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139096.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139098.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001391xx
file=DQM_V0001_Info_R000139100.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139102.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139103.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139195.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001392xx
file=DQM_V0001_Info_R000139239.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001393xx
file=DQM_V0001_Info_R000139347.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139356.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139360.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139362.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139363.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139364.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139365.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139368.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139370.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139372.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139375.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139399.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001394xx
file=DQM_V0001_Info_R000139400.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139407.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139411.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139455.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139457.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139458.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139459.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001397xx
file=DQM_V0001_Info_R000139779.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139780.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139781.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139783.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139784.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139786.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139788.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139789.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139790.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00013xxxx/0001399xx
file=DQM_V0001_Info_R000139965.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139966.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139967.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139968.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139969.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139971.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139972.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139973.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139974.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139975.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139976.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139978.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000139980.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001400xx
file=DQM_V0001_Info_R000140058.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140059.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140070.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140076.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001401xx
file=DQM_V0001_Info_R000140116.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140119.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140123.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140124.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140126.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140133.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140158.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140159.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140160.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140180.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140181.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140182.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001403xx
file=DQM_V0001_Info_R000140331.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140352.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140359.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140361.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140362.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140379.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140381.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140382.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140383.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140385.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140386.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140387.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140388.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000140399.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001404xx
file=DQM_V0001_Info_R000140401.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001418xx
file=DQM_V0001_Info_R000141865.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000141874.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000141876.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000141880.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000141881.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000141882.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001419xx
file=DQM_V0001_Info_R000141956.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000141957.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000141958.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000141959.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000141960.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000141961.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001420xx
file=DQM_V0001_Info_R000142035.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142036.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142038.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142039.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142040.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142076.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001421xx
file=DQM_V0001_Info_R000142128.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142129.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142130.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142132.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142135.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142136.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142137.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142187.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142188.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142189.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142191.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001422xx
file=DQM_V0001_Info_R000142264.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142265.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001423xx
file=DQM_V0001_Info_R000142303.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142304.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142305.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142308.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142309.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142311.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142312.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142313.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142315.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142317.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142318.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142319.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001424xx
file=DQM_V0001_Info_R000142413.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142414.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142415.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142417.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142418.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142419.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142420.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142422.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142461.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001425xx
file=DQM_V0001_Info_R000142503.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142513.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142514.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142523.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142524.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142525.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142528.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142530.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142535.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142537.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142557.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142558.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001426xx
file=DQM_V0001_Info_R000142653.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142655.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142657.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142658.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142659.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142660.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142661.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142662.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142663.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142664.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001429xx
file=DQM_V0001_Info_R000142928.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142931.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142933.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142934.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142935.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142936.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142953.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142954.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142955.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142970.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142971.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000142974.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001430xx
file=DQM_V0001_Info_R000143004.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143005.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143006.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143007.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143008.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001431xx
file=DQM_V0001_Info_R000143179.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143181.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143187.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143191.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143192.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143193.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001433xx
file=DQM_V0001_Info_R000143318.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143319.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143320.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143321.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143322.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143323.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143326.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143327.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143328.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143336.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001436xx
file=DQM_V0001_Info_R000143657.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143665.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001437xx
file=DQM_V0001_Info_R000143726.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143727.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143731.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001438xx
file=DQM_V0001_Info_R000143827.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143831.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143833.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143835.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001439xx
file=DQM_V0001_Info_R000143953.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143954.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143955.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143956.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143957.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143959.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143960.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143961.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000143962.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001440xx
file=DQM_V0001_Info_R000144010.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000144011.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000144083.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000144086.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000144089.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file

dir=00014xxxx/0001441xx
file=DQM_V0001_Info_R000144112.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
file=DQM_V0001_Info_R000144114.root
curl -4vLO --capath $X509_CERT_DIR --key $X509_USER_PROXY --cert $X509_USER_PROXY $server/$dir/$file
