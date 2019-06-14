<html>
<body>

# Simulación de Sensores e Integración en Plataformas Elasticsearch y Kibana

<p><b>Colaboradores</p></b>
<ul>
<li>Andrés Arias</li>
<li>Jorge S. Carranco</li>
<li>Génesis Vásquez</li>
</ul>

<p><b>Resumen del Proyecto</b></p>


<p><b>Archivos del Repositorio</b></p>
<ol>
<li>Arduino: Repositorio de....</li>
<li>Node-Red: Repositorio de....</li>
<li>Elasticsearch: Repositorio de....</li>
<li>Elasticsearch: Repositorio de....</li>
</ol>

<p><b>Instalación de Elasticsearch mediante Docker</b></p>
  
```powershell
sudo docker run\
  --name elasticsearch_container \
  -p 9200:9200 \
  -p 9300:9300 \
  -e "discovery.type=single-node" \
  docker.elastic.co/elasticsearch/elasticsearch:5.4.3
```

<p><b>Instalación de Kibana mediante Docker</b></p>
  
```powershell
sudo docker run \
  --name kibana \
  -p 5601:5601 \
  --link elasticsearch_container:elasticsearch_alias \
  -e "ELASTICSEARCH_URL=http://elasticsearch_alias:9200" \
  docker.elastic.co/kibana/kibana:5.4.3
```

<p><b>DSL Query útiles</b></p>
 
 Obtener los índices almacenados en Elasticsearch
```json
 GET /_cat/indices?v
 ```
Pone datos en el indice
 ```json
POST my_index/my_type/_id
{
  "value": "value"
}
 ```
</body>
</html>
