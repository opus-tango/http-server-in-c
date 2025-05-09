FROM ubuntu

RUN apt-get update && apt-get install -y build-essential

RUN mkdir /app
COPY *.c /app
COPY *.h /app
COPY Makefile /app
COPY /public /app/public

WORKDIR /app

RUN make release

CMD ["./webserver.out"]