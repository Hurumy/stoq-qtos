# stoq-qtos
Library to easily implement of quantum communication/BB84: stoq&amp;qtos


<img width="642" alt="Screenshot of stoq & qtos" src="https://github.com/user-attachments/assets/08b70a0a-7710-464e-9563-2492730a9064" />



## Setup
```make```


## How to encode
```./stoq $(STRING) $(GATES)```


example: ```./stoq "Hello world" "HXYZ"```



## How to decode
```./qtos $(GATES)```

example: ```./qtos "HXYZ"```


This command takes packet from stdin. you can do like this: ```./stoq "Hello world" "H" | ./qtos "H"```



## Gates you can use
- Hadamard gate
- Pauli-X gate
- Pauli-Y gate
- Pauli-Z gate


## Packet structure
```QBIT a:(0.0,0.0) b:(0.0,0.0) END```

<img width="510" alt="Screenshot 2025-01-23 at 17 34 20" src="https://github.com/user-attachments/assets/d1c356a6-6b9d-45f7-89fb-40a3ab902fa6" />


You have better idea? make an issue now!

