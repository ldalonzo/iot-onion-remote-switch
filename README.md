# IoT Onion Omega Smart Switch

![CMake](https://github.com/ldalonzo/iot-onion-remote-switch/workflows/CMake/badge.svg)

A smart switch powered by a MIPS32 24K CPU.

## Deploying to your target device
```bash
scp -oKexAlgorithms=+diffie-hellman-group1-sha1 onion-switch root@Omega-1EB3.local:onion-switch
```

```bash
ssh -oKexAlgorithms=+diffie-hellman-group1-sha1 root@Omega-ABCD.local
```
