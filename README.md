# IARS_Proyect
MSIET - IARS 



```powershell
sudo docker run\
  --name elasticsearch_container \
  -p 9200:9200 \
  -p 9300:9300 \
  -e "discovery.type=single-node" \
  docker.elastic.co/elasticsearch/elasticsearch:5.4.3
```


```powershell
sudo docker run \
  --name kibana \
  -p 5601:5601 \
  --link elasticsearch_container:elasticsearch_alias \
  -e "ELASTICSEARCH_URL=http://elasticsearch_alias:9200" \
  docker.elastic.co/kibana/kibana:5.4.3
```
