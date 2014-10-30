//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace Sup;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Contacts;
using namespace Windows::Phone;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

MainPage::MainPage()
{
	InitializeComponent();
	m_phoneNums = ref new Platform::Collections::Vector < String^ > ();
	m_listView->IsTextScaleFactorEnabled = true;
}

/// <summary>
/// Invoked when this page is about to be displayed in a Frame.
/// </summary>
/// <param name="e">Event data that describes how this page was reached.  The Parameter
/// property is typically used to configure the page.</param>
void MainPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	(void) e;	// Unused parameter

	// TODO: Prepare page for display here.

	// TODO: If your application contains multiple pages, ensure that you are
	// handling the hardware Back button by registering for the
	// Windows::Phone::UI::Input::HardwareButtons.BackPressed event.
	// If you are using the NavigationHelper provided by some templates,
	// this event is handled for you.
}
void MainPage::OnAddButtonPress(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto contactPicker = ref new Windows::ApplicationModel::Contacts::ContactPicker();
	contactPicker->DesiredFieldsWithContactFieldType->Append(ContactFieldType::PhoneNumber);
	concurrency::create_task(contactPicker->PickContactAsync()).then([this](Contacts::Contact ^contact) 
	{
		if (contact == nullptr)
			return;
		m_listView->Items->Append(contact->FirstName + " " + contact->LastName);
		for each (Contacts::ContactPhone ^phone in contact->Phones)
		{
			m_phoneNums->Append(phone->Number);
		}
	});
}

void MainPage::OnSupButtonPress(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Windows::ApplicationModel::Chat::ChatMessage ^msg = ref new Windows::ApplicationModel::Chat::ChatMessage();
	for each (Platform::String^ var in m_phoneNums)
	{
		msg->Recipients->Append(var);
	}
	msg->Body = "Sup!";
	Windows::ApplicationModel::Chat::ChatMessageManager::ShowComposeSmsMessageAsync(msg);
}