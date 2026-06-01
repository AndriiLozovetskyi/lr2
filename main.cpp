#include <iostream>
#include <string>
#include <map>

using namespace std;

class Message {
protected:
    string text;

public:
    Message(string txt = "") : text(txt) {}

    virtual Message* clone() const = 0;

    virtual void send() const = 0;

    void setText(const string& txt) {
        text = txt;
    }

    virtual ~Message() {}
};

class EmailMessage : public Message {
public:
    EmailMessage(string txt = "") : Message(txt) {}

    Message* clone() const override {
        return new EmailMessage(*this);
    }

    void send() const override {
        cout << "Email: " << text << endl;
    }
};

class SmsMessage : public Message {
public:
    SmsMessage(string txt = "") : Message(txt) {}

    Message* clone() const override {
        return new SmsMessage(*this);
    }

    void send() const override {
        cout << "SMS: " << text << endl;
    }
};

class PushMessage : public Message {
public:
    PushMessage(string txt = "") : Message(txt) {}

    Message* clone() const override {
        return new PushMessage(*this);
    }

    void send() const override {
        cout << "Push: " << text << endl;
    }
};

class MessageRegistry {
private:
    map<string, Message*> prototypes;

public:
    void addPrototype(
        const string& key,
        Message* prototype)
    {
        prototypes[key] = prototype;
    }

    Message* createMessage(
        const string& key)
    {
        return prototypes[key]->clone();
    }

    ~MessageRegistry() {
        for (auto& item : prototypes)
            delete item.second;
    }
};

int main() {

    MessageRegistry registry;

    registry.addPrototype(
        "email",
        new EmailMessage("Email Template")
    );

    registry.addPrototype(
        "sms",
        new SmsMessage("SMS Template")
    );

    registry.addPrototype(
        "push",
        new PushMessage("Push Template")
    );

    Message* m1 =
        registry.createMessage("email");

    m1->setText(
        "Welcome to our service"
    );

    m1->send();

    Message* m2 =
        registry.createMessage("sms");

    m2->setText(
        "Verification code: 1234"
    );

    m2->send();

    Message* m3 =
        registry.createMessage("push");

    m3->setText(
        "New discount available"
    );

    m3->send();

    delete m1;
    delete m2;
    delete m3;

    return 0;
}
