# IARS_Proyect
MSIET - IARS 




sudo docker run                        \
  --name elasticsearch_container  \
  -p 9200:9200                    \
  -p 9300:9300                    \
  -e "discovery.type=single-node" \
  docker.elastic.co/elasticsearch/elasticsearch:5.4.3
