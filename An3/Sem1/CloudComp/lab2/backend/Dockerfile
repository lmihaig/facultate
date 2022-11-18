FROM python:3.10-slim

WORKDIR /app

COPY requirements.txt .

RUN pip3 install -r requirements.txt

COPY . .

# RUN pytest

CMD ["flask", "--debug", "run", "--host=0.0.0.0"]