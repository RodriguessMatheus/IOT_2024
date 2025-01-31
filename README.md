# Iot2024

Desenvolvi o projeto no SENAI onde sensores em um ESP32 capturam dados e os enviam em JSON via MQTT para a AWS, garantindo comunicação eficiente e segura com certificados e um broker próprio. Isso possibilita um fluxo contínuo de informações em tempo real.
Para otimizar a visualização e controle dos dispositivos, implementei uma dashboard interativa no Node-RED rodando em uma instância EC2, permitindo uma gestão remota eficiente dos dados coletados.

Esse código em C++ deu funcionalidade para cada sensor no projeto enviando os dados para a nuvem, nesse projeto mostra cada arquivo em (.cpp) e (.h) e suas funcionalidades, no main.cpp está todas as funções projetadas em arquivos .cpp assim enviando em um formato json todos os dados, ja no iot.h tem como a manipulação dos dados colocando em prática o controle dos sensores por IOT
