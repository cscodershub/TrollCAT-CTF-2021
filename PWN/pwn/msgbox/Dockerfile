FROM ubuntu:18.04

RUN apt-get update && apt-get dist-upgrade -y &&apt-get install -y socat && rm -rf /var/lib/apt/lists/ 
RUN useradd ctf
ADD flag /
RUN chmod 444 /flag
ADD vuln /
USER ctf

EXPOSE 1337
CMD [ "socat", "tcp-listen:1337,fork,reuseaddr", "exec:/vuln"]
