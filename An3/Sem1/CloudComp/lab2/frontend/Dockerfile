FROM node:18-alpine3.16

RUN npm i -g serve

WORKDIR /app

COPY package*.json ./

RUN npm install

COPY . .

RUN npm run build

EXPOSE 5000

CMD [ "npm", "run", "serve" ]