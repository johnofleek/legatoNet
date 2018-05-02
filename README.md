## Legato getaddrinfo

This is a service to workaround the problem that getaddrinfo doesn't seem to work in sandboxed apps


# Legato Command line build

From project root  

**Set the cross build environment**  

source ~/legato/packages/legato.sdk.latest/resources/configlegatoenv

**Build for wp85**  

```
make wp85
```


** install from host (assumes target is 192.168.2.2)**  

```
make install 
```

# Example call
```
            // This is a function call to legato service net - replaces getaddrinfo() because of sandbox issue
            net_getAddrInfo
            (
                hints.ai_family,    // int32_t hints_ai_family,    < [IN]
                hints.ai_socktype,  // int32_t hints_ai_socktype,  < [IN]
                hints.ai_protocol,  // int32_t hints_ai_protocol,  < [IN]
                host,               // const char* host,           < [IN]
                ipAddressAsString,  // char* ipAddressAsString,    < [OUT]
                NET_MAX_STRLEN_IP   // size_t ipAddressAsStringNumElements < [IN]
            );
```
# Example binding in .adef
bindings:
{
		mqttClient.mqttClientComponent.net -> net.net
}



# GIT  

## Git clone the project  

```
git clone https://github.com/johnofleek/legatoNet.git
```


## Git "checkin"

```
git add .
git commit -m "your comment"
git push -u origin master
```

## Git "checkout"

```
git pull origin master
```


