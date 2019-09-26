//    const functions = require('firebase-functions');
//    const admin = require('firebase-admin');
//    admin.initializeApp();
//    admin.initializeApp(functions.config().firebase);
//    const DialogflowApp = require('actions-on-google').DialogflowApp;

//    exports.receiveAssistantRequests = functions.https.onRequest((request, response) => {
//    const app = new DialogflowApp({ request: request, response: response });

//    function handlerRequest(app) {

//        const device = app.getArgument('devices');
//        const status = app.getArgument('status');

//        return admin.database().ref(`/automation/${device}/value`).set(status)
//            .then(snapshot => {
//                app.ask(`Ok, switching ${device} ${status}. Do you want to control anything else?`);
//            });

//    }
//    app.handleRequest(handlerRequest);
//  });


const functions = require('firebase-functions');
const admin = require('firebase-admin');
admin.initializeApp();

const { dialogflow } = require('actions-on-google');
const app = dialogflow();

app.fallback((conv, { devices, status }) => {
	return admin.database().ref(`/automation/${devices}/value`).set(status)
		.then(snapshot => {
			conv.ask(`Ok, switching ${devices} ${status}. Do you want to control anything else?`);
		});
});

exports.receiveAssistantRequests = functions.https.onRequest(app);
