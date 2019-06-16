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
<p>En el siguiente proyecto se desarrolla un sistema de simulación de datos de sensores medioambientales en tiempo real (temperatura, humedad, viento, presión, e índice UV) para un total de 5 lugares en la ciudad de Sevilla, España. Los datos simulados de estas localizaciones serán almacenados en un servidor web para luego ser mostrados mediante gráficas en Kibana (dashboards). </p>

<p><b>Archivos del Repositorio</b></p>
<ol>
<li>Arduino: Repositorio del programa de Arduino para la simulación de sensores y del programa usado para testear el sensor DHT11</li>
<li>Node-Red: Repositorio de el flow donde se encuentran los nodos configurados, además se incluye el código del nodo ELASTIC INSET DATA  </li>
<li>Elasticsearch: Repositorio del código de creación del índice y el código para borrar los datos del índice</li>
<li>Kibana: Repositorio de los dashboards creados en Kibana</li>
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
