/*
** EPITECH PROJECT, 2026
** Project - Arcade
** File description:
** Header file for
** everything related
** to displays / graphics
*/

#pragma once

#include "utils/shapes.hpp"
#include "utils/events.hpp"
#include "utils/text.hpp"
#include <string_view>
#include <optional>


namespace Arcade {
    class IDisplay {
        public:
            virtual ~IDisplay() = default;


            ////////////////////////////////////////////////////
            //                                                //
            //                Startup / Cleanup               //
            //                                                //
            ////////////////////////////////////////////////////

            /**
             * Opens a new window to allow
             * using this display's render
             * functions.
             *
             * A call to open() *must* imperatively
             * be done before calling any rendering
             * method from the IDisplay.
             */
            virtual void open() = 0;

            /**
             * Closes the display's window
             * (if opened). This should also
             * deallocate any heavy resources
             * the display has allocated.
             */
            virtual void close() noexcept = 0;

            /**
             * Determines if the display's
             * window is currently open
             * or not.
             */
            virtual bool isOpen() const noexcept = 0;


            ////////////////////////////////////////////////////
            //                                                //
            //                    Rendering                   //
            //                                                //
            ////////////////////////////////////////////////////

            /**
             * Clears the display's
             * window, rendering it
             * completely black.
             */
            virtual void clear() = 0;

            /**
             * Updates the display's
             * window to show what's
             * been drawn since the
             * last call to clear().
             */
            virtual void display() = 0;

            /**
             * Draws a 1x1 point onto
             * the display's internal
             * window.
             */
            virtual void draw(const Shapes::Point& point) = 0;

            /**
             * Draws the rectangle onto
             * the display's internal
             * window.
             */
            virtual void draw(const Shapes::Rectangle& rect) = 0;

            /**
             * Draws the given text onto
             * the display's internal window.
             */
            virtual void draw(const Text& text) = 0;


            ////////////////////////////////////////////////////
            //                                                //
            //                Event Management                //
            //                                                //
            ////////////////////////////////////////////////////

            /**
             * Polls for a single event.
             *
             * If no event is currently queued or
             * actioned, none is returned.
             */
            virtual std::optional<Event> pollEvent() = 0;

            /**
             * Retrieves the coordinates of the mouse
             * on the display's window.
             *
             * Note:
             * This function should *only* be called if
             * a mouse event was received.
             * The reason for this is that, depending on
             * the display, the mouse coordinates may only
             * be updated when a mouse-related event occurs
             * (as with the NCurses library).
             */
            virtual std::pair<Coordinate, Coordinate> mousePosition() const = 0;

            ////////////////////////////////////////////////////
            //                                                //
            //                  Display Info                  //
            //                                                //
            ////////////////////////////////////////////////////

            /**
             * Retrieves the display window's size
             * in cell distance.
             *
             * For instance, on a 1920x1080 window
             * with a cell size of 10x20, this function
             * would return { 1920 / 10, 1080 / 20 }.
             */
            virtual std::pair<Coordinate, Coordinate> size() const noexcept = 0;

            /**
             * Retrieves the name of the graphics
             * library the IDisplay implementation
             * uses. The name should be user-friendly
             * to allow it to be used when implementing
             * a selection menu.
             *
             * Note:
             * Returning a std::string will inevitably
             * return in errors and undefined behaviour.
             *
             * This function is intended to return a literal
             * string, such as:
             *
             * ```
             * std::string_view libraryName() const noexcept override { return "libcaca"; }
             * ```
             */
            virtual std::string_view libraryName() const noexcept = 0;
    };
}
