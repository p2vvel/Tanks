import TanksServer from "./tanks_server.js";



const port = process.argv[2] || 3003;;
console.log(`Server running at port ${port}`);
const Server = new TanksServer(port);