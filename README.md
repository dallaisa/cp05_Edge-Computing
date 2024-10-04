# Equipe de Desenvolvimento
Este projeto foi desenvolvido por:

- Camila Pedroza da Cunha (RM 558768)
- Isabelle Dallabeneta (RM 554592)
- Nicolli Kassa (RM 559104)
- Pedro Camacho (RM 556831)

## Introdução
Este documento apresenta uma visão geral do projeto de monitoramento do ambiente da Vinheria, abordando os componentes utilizados e os requisitos da fase dois do projeto. O sistema tem como objetivo garantir as condições ideais de armazenamento dos vinhos, monitorando temperatura, umidade e luminosidade, e permitindo a análise de dados históricos.

## Componentes do Projeto

### ESP32
O ESP32 é um microcontrolador com Wi-Fi e Bluetooth integrados, ideal para aplicações IoT. Ele será utilizado como a unidade de controle principal do sistema, coletando dados dos sensores e enviando-os para a plataforma de back-end FIWARE.

### Jumpers
Os jumpers são fios de conexão utilizados para realizar ligações entre o ESP32 e os sensores. Eles garantem a comunicação e a alimentação elétrica necessária para o funcionamento dos dispositivos.

### Resistores
Os resistores são componentes eletrônicos que limitam a corrente elétrica em um circuito. Eles são essenciais na conexão de sensores, como o DHT22, para garantir que os níveis de tensão estejam dentro das especificações corretas.

### Sensor de Temperatura e Umidade (DHT22)
O DHT22 é um sensor digital que mede a temperatura e a umidade do ambiente. Ele será utilizado para coletar dados críticos sobre as condições do depósito, permitindo o monitoramento em tempo real.

### Sensor de Luminosidade (LDR)
O sensor de luminosidade LDR (Light Dependent Resistor) detecta a intensidade da luz no ambiente. Com isso, será possível acionar alertas quando os níveis de luz forem excessivos, garantindo a proteção dos vinhos.

## Feedback dos Proprietários
Após a apresentação da primeira fase do projeto, os proprietários expressaram satisfação, mas também levantaram questões importantes:

1. Necessidade de monitoramento contínuo da temperatura e umidade.
2. Requisitos de dados históricos para análises e rastreabilidade.
3. Integração com distribuidoras na Europa.
4. Importância de exportação de dados para relatórios e gráficos.

## Requisitos da Fase Dois
Para atender ao feedback recebido, os seguintes requisitos foram estabelecidos:

1. **Smart Data Models**: Implementar modelos de dados que sigam as diretrizes da União Europeia e o padrão NGSIv2 do FIWARE.
2. **Back-end FIWARE**: Utilizar o FIWARE como plataforma de back-end para interconectar o sistema ao ecossistema de negócios europeu.
3. **Protocolos MQTT e NGSI**: Enviar os dados coletados via MQTT e garantir que as informações estejam em conformidade com NGSI.
4. **Armazenamento Histórico de Dados**: Implementar um sistema que armazene as leituras históricas de temperatura, umidade e luminosidade.

## Principais Requisitos Técnicos
1. **Envio de Dados**: Os dados coletados pelos sensores devem ser enviados para a plataforma FIWARE através do protocolo MQTT.
2. **Time Stamp**: Cada leitura deve incluir um carimbo de data/hora (timestamp).
3. **Comunicação Wi-Fi**: O ESP32 deve se conectar à internet para enviar as informações coletadas.
4. **Interface NGSI**: A interface de acesso às informações deve ser compatível com o NGSI (Next Generation Service Interface).

## Conclusão
A fase dois do projeto visa não apenas atender às necessidades atuais dos proprietários da Vinheria, mas também preparar o sistema para futuras integrações e expansões, garantindo a eficiência na gestão das condições de armazenamento dos vinhos. A adoção de padrões como NGSI e o uso do FIWARE serão fundamentais para o sucesso dessa implementação.

