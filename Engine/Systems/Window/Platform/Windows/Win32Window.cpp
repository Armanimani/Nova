#include "Engine/Logging/ConsoleLogger.hpp"
#include "Engine/Systems/Window/Platform/Windows/Win32Window.hpp"
#include "Engine/Systems/Window/Event/window_events.hpp"

#include <string>

namespace nova
{
	Win32Window::Win32Window(const WindowSettings& settings, EventManager* event_manager)
		: event_manager{ event_manager }
	{
		if (!is_initialized)
		{
			initialize();
		}
		createWindow(settings);
	}

	Win32Window::~Win32Window()
	{
		close();
	}

	void Win32Window::initialize() noexcept
	{
		initializeInstanceHandle();
		registerWindowClass();
		is_initialized = true;
	}

	void Win32Window::registerWindowClass() noexcept
	{
		WNDCLASSEX wc{};
		wc.cbSize = sizeof(wc);
		wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = windowProcCallback;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = handle_instance;
		wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = L"Nova";

		if (!RegisterClassEx(&wc))
		{
			createErrorMessage("Windows class registration failed!");
		}
	}
	
	void Win32Window::createWindow(const WindowSettings& settings) noexcept
	{
		RECT rect{};
		rect.left = settings.initial_position_x;
		rect.top = settings.initial_position_y;
		rect.right = settings.initial_width;
		rect.bottom = settings.initial_height;

		const DWORD dwStyle = WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW;
		const DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

		AdjustWindowRectEx(&rect, dwStyle, false, dwExStyle);

		const auto window_x = settings.initial_position_x;
		const auto window_y = settings.initial_position_y;
		const auto window_width = rect.right - rect.left;
		const auto window_height = rect.bottom - rect.top;

		handle = CreateWindowEx(
			dwExStyle, L"Nova", std::wstring(settings.title.cbegin(), settings.title.cend()).c_str(), dwStyle,
			window_x, window_y, window_width, window_height,
			nullptr, nullptr, handle_instance, nullptr
		);

		if (!handle)
		{
			createErrorMessage("Unable to create window");
			return;
		}

		registerWindow(handle, this);
	}

	void Win32Window::handleWindowEvent(const UINT message, [[maybe_unused]] const WPARAM w_param, const LPARAM l_param) const noexcept
	{
		switch(message)
		{
			case WM_SIZE:
			{
				const auto width = static_cast<UInt32>(LOWORD(l_param));
				const auto height = static_cast<UInt32>(HIWORD(l_param));
				event_manager->addEvent<WindowResizeEvent>(std::make_unique<WindowResizeEvent>(width, height));
				break;
			}
			case WM_SETFOCUS:
			{
				event_manager->addEvent<WindowFocusEvent>(std::make_unique<WindowFocusEvent>(true));
				break;
			}
			case WM_KILLFOCUS:
			{
				event_manager->addEvent<WindowFocusEvent>(std::make_unique<WindowFocusEvent>(false));
				break;
			}
			case WM_CLOSE:
			{
				event_manager->addEvent<WindowCloseEvent>(std::make_unique<WindowCloseEvent>());
				break;
			}
			case WM_DESTROY:
			{
				event_manager->addEvent<WindowDestroyEvent>(std::make_unique<WindowDestroyEvent>());
				break;
			}
			case WM_SHOWWINDOW:
			{
				event_manager->addEvent<WindowShowEvent>(std::make_unique<WindowShowEvent>());
				break;
			}
			case WM_CREATE:
			{
				if (this != nullptr)
					event_manager->addEvent<WindowCreateEvent>(std::make_unique<WindowCreateEvent>());
				break;
			}
			default:
			{
				break;
			}
		}
	}

	void Win32Window::handleKeyboardEvent(UINT message, WPARAM w_param, LPARAM l_param) noexcept
	{
		// TODO: Add the keyboard events
	}
	
	void Win32Window::handleMouseEvent(UINT message, WPARAM w_param, LPARAM l_param) noexcept
	{
		// TODO: add mouse events
	}

	void* Win32Window::getHandle() const noexcept
	{
		return static_cast<void*>(handle);
	}

	void Win32Window::close() const noexcept
	{
		CloseWindow(handle);
	}

	void Win32Window::focus() const noexcept
	{
		SetFocus(handle);
	}

	void Win32Window::setSize(const Int32 x, const Int32 y, const Int32 width, const Int32 height) const noexcept
	{
		SetWindowPos(handle, nullptr, x, y, width, height, SWP_NOZORDER);
	}
	
	Int32 Win32Window::getWidth() const noexcept
	{
		RECT rect{};
		GetWindowRect(handle, &rect);
		return rect.right - rect.left;
	}
	
	Int32 Win32Window::getHeight() const noexcept
	{
		RECT rect{};
		GetWindowRect(handle, &rect);
		return rect.top - rect.bottom;
	}
	
	void Win32Window::maximize() const noexcept
	{
		ShowWindow(handle, SW_MAXIMIZE);
	}
	
	void Win32Window::minimize() const noexcept
	{
		ShowWindow(handle, SW_MINIMIZE);
	}
	
	void Win32Window::restore() const noexcept
	{
		ShowWindow(handle, SW_RESTORE);
	}
	
	void Win32Window::show() const noexcept
	{
		ShowWindow(handle, SW_SHOW);
	}
	
	void Win32Window::hide() const noexcept
	{
		ShowWindow(handle, SW_HIDE);
	}
	
	Bool Win32Window::isMaximized() const noexcept
	{
		return IsZoomed(handle);
	}
	
	Bool Win32Window::isMinimized() const noexcept
	{
		return IsIconic(handle);
	}
	
	Bool Win32Window::isVisible() const noexcept
	{
		return IsWindowVisible(handle);
	}

	Bool Win32Window::isFocused() const noexcept
	{
		return (GetFocus() == handle);
	}

	void Win32Window::registerWindow(HWND handle, Win32Window* window) noexcept
	{
		window_registry[handle] = window;
	}
	
	Win32Window* Win32Window::getWindow(HWND handle) noexcept
	{
		return window_registry[handle];
	}

	void Win32Window::initializeInstanceHandle() noexcept
	{
		handle_instance = GetModuleHandle(nullptr);
		if (!handle_instance)
		{
			createErrorMessage("Unable to get the module handle");
		}
	}

	void Win32Window::createErrorMessage(const std::string& message)  noexcept
	{
		const UInt32 error = GetLastError();
		ConsoleLogger::logCritical("Nova", message + " ErrorCode: " + std::to_string(error));
		MessageBox(nullptr, LPCWSTR(message.c_str()), L"Error", MB_ICONEXCLAMATION | MB_OK);
	}

	void Win32Window::update() const noexcept
	{
		MSG message{};
		while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}

	LRESULT CALLBACK Win32Window::windowProcCallback(HWND handle, const UINT message, const WPARAM w_param, const LPARAM l_param)
	{
		const auto window = getWindow(handle);

		switch (message)
		{
			case WM_CREATE:
			case WM_DESTROY:
			case WM_SIZE:
			case WM_SETFOCUS:
			case WM_KILLFOCUS:
			case WM_CLOSE:
			case WM_SHOWWINDOW:
			{
				window->handleWindowEvent(message, w_param, l_param);
				break;
			}
			case WM_KEYDOWN:
			case WM_KEYUP:
			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
			{
				window->handleKeyboardEvent(message, w_param, l_param);
				break;
			}
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
			case WM_MBUTTONDOWN:
			case WM_MBUTTONUP:
			case WM_MOUSEHWHEEL:
			case WM_MOUSEMOVE:
			{
				window->handleMouseEvent(message, w_param, l_param);
				break;
			}
			default:
			{
				break;
			}
		}
		return DefWindowProc(handle, message, w_param, l_param);
	}
}
