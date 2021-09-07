# Connect from azure portal bash shell to webvm
ssh -i ~/.ssh/id_rsa azureuser@20.194.50.238

# Install MongoDB Community Edition
```
wget -qO - https://www.mongodb.org/static/pgp/server-4.4.asc | sudo apt-key add -
# The operation should respond with an OK.

echo "deb [ arch=amd64,arm64 ] https://repo.mongodb.org/apt/ubuntu bionic/mongodb-org/4.4 multiverse" \
| sudo tee /etc/apt/sources.list.d/mongodb-org-4.4.list

sudo apt-get update
sudo apt-get install -y mongodb-org
```
---
# Start/Stop the db
_Start_
`sudo systemctl start mongod`
_Status_
`sudo systemctl status mongod`
_Run with system_
`sudo systemctl enable mongod`
_Stop_
`sudo systemctl stop mongod`
_Restart_
`sudo systemctl restart mongod`
_Run MongoDB with default port 27017_
`mongo`
---

# Run mongoDB
```
$ mongo
```
# Create a database to work
```
> use local_dc
```
# Create users in mongoDB after creating a database
```
# Admin user
> db.createUser({
... user:"datagen" , pwd : passwordPrompt(), 
... roles:[
... {role: "readWriteAnyDatabase", db:"admin"}]
... {role: "dbAdminAnyDatabase", db:"admin"}]
... {role: "userAdminAnyDatabase", db:"admin"}]
... })
# pw for datagen: neyuq
# readWrite user
> db.createUser({user:"db_write", pwd:"12345", roles:[{role: "readWrite", db:"local_dc"}]})
# readonly user
> db.createUser({user:"db_read", pwd:"reader123", roles:[{role: "read", db:"local_dc"}]})
```

# Login from external
- Modify /etc/mongod.conf
```
security
  authorization: 'enable'

# networkings
net
  port: 27017
  bindId: 127.0.0.1, 0.0.0.0
```
- Connection strings
> External
```
mongo "mongodb://db_write:12345@13.67.92.248:27017/local_dc"
```
> Internal
```
mongo "mongodb://db_datagen@127.0.0.1:27017/local_dc"
```

# Create collection (~table)
```db.COLLECTION_NAME.insert(document)```
db.change_log.insert({
    tag: "1",
    change: "insert dummy tag",
    in_charge: "data_extration",
    updated_at: new Timestamp(),
    {"$project": { 
        "update_date": {
            "$dateToString" : {"date": new Date(), "format": "%Y-%m-%d"},
        }
    }}
})
# Create documents (~rows)

# Update documents


# Run locally
docker run -it -p 8080:8080 qsproductionacr.azurecr.io/local-dc:storage-dev

# Run on remote
docker login qsproductionacr.azurecr.io
u: qsproductionacr 
p: gfRdrq5EoUib/rCnBl3GdCOy8svSc3DK

```console
docker push qsproductionacr.azurecr.io/local-dc:storage

docker run -d --pull always --rm --name storage -p 8080:8080 qsproductionacr.azurecr.io/local-dc:storage
```

Adult: 3.212.500 (Chinh) + 2.200.000 (Bo sung) + 594.000 (Nha khoa) = 6.006.500
Children (5 yo): 3.495.750 (Chinh) + 2.420.000 (Bo sung) + 653.400 (Nha khoa) = 6.569.150

net = nn.DataParallel(model, device_ids=list(range(torch.cuda.device_count())))

absl-py idna pillow keras-applications ipywidgets widgetsnbextension dataclasses termcolo
libssh2 pyyaml cudatoolkit freeglut glib python xorg-libxfixes pyrsistent libuuid cryptography