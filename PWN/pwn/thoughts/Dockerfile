FROM ubuntu:20.04
RUN dpkg --add-architecture i386
RUN apt-get update && apt-get dist-upgrade -y &&apt-get install -y socat build-essential libc6:i386 libncurses5:i386 libstdc++6:i386 && rm -rf /var/lib/apt/lists/ 
RUN useradd ctf
ADD flag /
RUN chmod 444 /flag
ADD vuln /
USER ctf

EXPOSE 1337
CMD [ "socat", "tcp-listen:1337,fork,reuseaddr", "exec:/vuln"]
