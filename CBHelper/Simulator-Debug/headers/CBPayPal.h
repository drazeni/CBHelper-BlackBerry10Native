/* Copyright (c) 2013 Cloudbase.io Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <string>
#include <vector>
#include "CBSerializable.h"

namespace Cloudbase {

#ifndef CBPAYPAL_H
#define CBPAYPAL_H


/***
 * this object represents a single item within a CBPayPalBill object.
 */
class CBPayPalBillItem : public CBSerializable {
public:
	std::string name; /// The name of the item for the transaction
	std::string description; /// An extended description of the item. This should also contain the amount as PayPal does not always display it.
	double amount; /// The amount of the transaction
	double tax; /// additional taxes to be added to the amount
	int quantity; /// a quantity representing the number of items involved in the transaction. for example 100 poker chips

	CBPayPalBillItem();

	std::string serialize();
};

/**
 * This is the bill object for the PayPal digital goods payments APIs. A bill object must contain
 * at least one BillItem.
 *
 * The description of the bill should also contain the total amount as PayPal does not always display
 * the amount in the checkout page.
 */
class CBPayPalBill : public CBSerializable {
public:
	std::string name; /// a name for the purchase
	std::string description; /// a description of the bill item. this should also contain the price for the bill as PayPal will not always display the amount field.
	std::string invoiceNumber; /// this is a user generated unique identifier for the transaction.
	std::vector<CBPayPalBillItem> items; /// this is a list of BillItems. Each CBPayPalBill must have at least one BillItem
	std::string currency; /// The 3 letter ISO code for the transaction currency. If not specified this will automatically be USD
	std::string paymentCompletedFunction; /// This is the code of a CloudFunction to be executed once the payment is completed
	std::string paymentCancelledFunction; /// This is the name of a CloudFunction to be executed if the payment is cancelled
	/**
	 * By default the express checkout process will return to the cloudbase APIs. if you want to override
	 * this behaviour and return to a page you own once the payment is completed set this property to the url
	 */
	std::string paymentCompletedUrl;
	/**
	 * By default the express checkout process will return to the cloudbase APIs. if you want to override
	 * this behaviour and return to a page you own once the payment has been cancelled set this property to the url
	 */
	std::string paymentCancelledUrl;

	CBPayPalBill();

	void addItem(CBPayPalBillItem newItem);

	std::string serialize();
};

#endif

}
