//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace Sup
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();
	private:
		void OnAddButtonPress(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnSupButtonPress(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
	private:
		Platform::Collections::Vector<Platform::String^>^ m_phoneNums;
	};
}
