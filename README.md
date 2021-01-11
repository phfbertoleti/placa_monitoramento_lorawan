# Placa - Monitoramento LoRaWAN / manutenção preventiva

Este é o repositório oficial da placa "Monitamento LoRaWAN" / placa "manutenção preventiva". Esta placa é um projeto open-source de minha autoria para monitamento de variáveis via LoRaWAN e para uso em algumas aplicações de manutenção preventiva. Este projeto faz uso do módulo Heltec wifi LoRa V1 (com conectividades LoRa/LoRaWAN, BLE e wi-fi).


![Placa monitoramento LoRaWAN / manutenção preventiva](https://github.com/phfbertoleti/placa_monitoramento_lorawan/master/Imagens/placa_montada.jpg)

## Princípio de funcionamento

Essa placa tem objetivo de facilitar o desenvolvimento de protótipos em Internet das Coisas, principalmente para aqueles focados em monitoramento remoto e manutenção preventiva. Para facilitar a montagem e uso, o Heltec wifi LoRa V1 e os módulos sensores são conectados em soquetes / barras de pinos do tipo fêmea. 
A placa suporta os seguintes módulos sensores:

* Módulo MPU6050
* Módulo BMP180

Ainda, a placa possui entrada digital (3.3V - 12V), que pode ser usada também para entradas pulsadas.

Quanto à alimentação, essa placa permite:
- Ser alimentada com bateria (LiPo ou Li-Ion, de 1 célula), com recarga por energias renováveis (7V - 12V), até 3 fontes diferentes de energias renováveis, desde que na mesma tensão.
- Ser alimentada por fonte 5V/2A via conector micro-USB.

Para facilitar o uso, a placa possui furação idêntica ao Arduino UNO. Dessa forma, fica mais simples projetar cases ou utilizar cases já fabricados.

## Funcionalidades

Esta placa, usada juntamente com um módulo Heltec wifi LoRa V1 e os sensores que a placa suporta, compreende as seguintes funcionaliades:
 
* Conectividades wifi, Bluetooth (BLE e clássico), LoRa e LoRaWAN.
* Medição de temperatura
* Medição de pressão barométrica
* Medição de aceleração (3 eixos)
* Giroscópio (3 eixos)
* Exibição de textos e imagens em display OLED 0.96" (azul)
* Recarga de bateria via energias renováveis

## O que está disponivel neste repositório?

Resposta curta: 100% do projeto. Ou seja:

* Projeto completo de hardware (feito no KiCad 5.1.5)
* Arquivos gerber, já nos padrões para fabricação exigidos pela JLCPCB (www.jlcpcb.com)
* Softwares de exemplo (todos feitos na Arduino IDE, fazendo uso de bibliotecas populares e consagradas)
* Lista de materiais (BOM)

Para ver a BOM interativa, [clique aqui](https://htmlpreview.github.io/?https://github.com/phfbertoleti/placa_monitoramento_lorawan/blob/master/Hardware/BOM/ibom.html)

## Desejo contribuir com novas funcionalidades ou correções. Sou bem vindo?

Claro. Sinta-se a vontade para contribuir com o projeto. Toda melhoria é bem vinda!

## Gostei do seu trabalho. Onde consigo mais coisas publicadas por você?

Visite meu [site pessoal](http://www.pedrobertoleti.com.br) para ter acesso a quase tudo que publico no Brasil e exterior.