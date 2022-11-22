FROM node:18-alpine3.16
WORKDIR /app
COPY package*.json ./
RUN npm install
COPY . .
ARG API_URL
ENV VUE_APP_API_URL=$API_URL
RUN npm run build
CMD [ "npm", "run", "serve" ]