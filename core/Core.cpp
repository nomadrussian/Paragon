#include "Core.hpp"

#include <util/Log.hpp>

#include <cassert>

#include <GLFW/glfw3.h>

#include "asset/AssetManager.hpp"
#include "event/CoreEventManager.hpp"
#include "render/RenderHandler.hpp"
#include "render/ShaderManager.hpp"

template<>
Core* Singleton<Core>::instance = nullptr;

Core::Core()
{
    log_debug("Initializing AssetManager...");
    AssetManager::init();

    log_debug("Initializing graphics...");
    initGraphics();

    log_debug("Initializing CoreEventManager...");
    CoreEventManager::init();

    log_debug("Initializing InputHandler...");
    inputHandler = std::make_unique<InputHandler>();
    inputHandler->setGLFWwindow(mainWindow->getGLFWwindow());
    inputHandler->setKeyCallback();
    inputHandler->setMouseCallback();

    log_debug("Building CoreEventTypeGraph...");
    CoreEventTypeGraph::init();

    log_debug("Initializing input listeners...");
    keyboardListener = std::make_shared<KeyboardListener>();
    mouseListener = std::make_shared<MouseListener>();
    keyboardListener->init();
    mouseListener->init();

    log_debug("Core initialization has been completed");
}

Core::~Core()
{
    log_debug("Shutting down Core...");
    glfwTerminate();

    log_debug("Core has been shut down");
}

void Core::initGraphics()
{
    log_debug("Setting up MainWindow...");
    mainWindow = std::make_unique<MainWindow>(1600, 900);

    log_debug("Initializing ShaderManager...");
    ShaderManager::init();

    log_debug("Initializing RenderHandler...");
    RenderHandler::init();

    log_debug("Graphics initialization has been completed");
}

void Core::setApplicationInstance(std::unique_ptr<Application> applicationInstance)
{
    this->applicationInstance = std::move(applicationInstance);
}

void Core::run()
{
    log_debug("Initializing Paragon...");
    applicationInstance->init();

    log_debug("Running Paragon...");
    while(!glfwWindowShouldClose(mainWindow->getGLFWwindow()))
    {
        float currentFrameTime = static_cast<float>(glfwGetTime());
        deltaTime = currentFrameTime - lastFrameTime;

        inputHandler->watchForHeldKeys();

        applicationInstance->update();
        RenderHandler::getInstance().renderScene();
        RenderHandler::getInstance().renderText(U"!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~", 10, 50, 22, RenderHandler::getInstance().textRenderer.getConsoleFont());
        RenderHandler::getInstance().renderText(U"¡¢£¤¥¦§¨©ª«¬®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ", 10, 100, 22, RenderHandler::getInstance().textRenderer.getConsoleFont());
        RenderHandler::getInstance().renderText(U"ĀāĂăĄąĆćĈĉĊċČčĎďĐđĒēĔĕĖėĘęĚěĜĝĞğĠġĢģĤĥĦħĨĩĪīĬĭĮįİıĲĳĴĵĶķĸĹĺĻļĽľĿŀŁłŃńŅņŇňŉŊŋŌōŎŏŐőŒœŔŕŖŗŘřŚśŜŝŞşŠšŢţŤťŦŧŨũŪūŬŭŮůŰűŲųŴŵŶŷŸŹźŻżŽžſ", 10, 150, 18, RenderHandler::getInstance().textRenderer.getConsoleFont());
        RenderHandler::getInstance().renderText(U"ƀƁƂƃƄƅƆㄈƇƈƉƊƋƌƍƎƏƐƑƒƓƔƕƖƗƘƙƚƛƜƝƞƟƠơƢƣƤƥƦƧƨƩƪƫƬƭƮƯưƱƲƳƴƵƶƷƸƹƺƻƼƽƾƿǀǁǂǃǄǅǆǇǈǉǊǋǌǍǎǄǅǆǇǈǉǊǋǌǏǐǑǒǓǔǕǖǗǘǙǚǛǜǝǞǟǠǡǢǣǤǥǦǧǨǩǪǫǬǭǮǯǰǱǲǳǴǵǶǷǸǹǺǼǽǾǿȀȁȂȃȄȅȆȇȈȉȊȋȌȍȎȏȐȑȒȓȔȕȖȗȘșȚțȜȝȞȟȠȡȢȣȤȥȦȧȨȩȪȫȬȭȮȯȰȱȲȳȴȵȶȷȸȹȺȻȼȽȾȿ", 10, 200, 13, RenderHandler::getInstance().textRenderer.getConsoleFont());
        RenderHandler::getInstance().renderText(U"           ‐‑‒–—―‖‗―‗†‡•‣․‥…‧‰                      ′″‴‵‶‷‸‹›‼‽⁇⁈⁉℀℁℃℉№™Ω℩℮ℯℰℱℲℳℴℵℶℷℸℹ℺℻ℼℽℾℿ", 10, 250, 32, RenderHandler::getInstance().textRenderer.getConsoleFont());
        RenderHandler::getInstance().renderText(U"⁰ⁱ⁴⁵⁶⁷⁸⁹⁺⁻⁼⁽⁾ⁿ₀₁₂₃₄₅₆₇₈₉₊₋₌₍₎", 10, 300, 22, RenderHandler::getInstance().textRenderer.getConsoleFont());
        RenderHandler::getInstance().renderText(U"€", 10, 350, 22, RenderHandler::getInstance().textRenderer.getConsoleFont());
        RenderHandler::getInstance().renderText(U"£", 10, 400, 22, RenderHandler::getInstance().textRenderer.getConsoleFont());
        RenderHandler::getInstance().renderText(U"℀℁ℂ℃℄℅℆ℇ℈℉ℊℋℐℑℒℓ℔ℕ№℗℘ℙℚℛℜ℞℟℠℡™℣ℤ℥Ω℧ℨ℩KÅℬℭ℮ℯℰℱℲℳℴℵℶℷℸℹ℺℻ℼℽℾℿ", 10, 450, 12, RenderHandler::getInstance().textRenderer.getConsoleFont());
        RenderHandler::getInstance().renderText(U"∀∁∂∃∄∅∆∇∈∉∊∋∌∍∎∏∐∑−∓∔∕∖∗∘∙√∛∜∝∞∟∠∡∢∣∤∥∦∧∨∩∪∫∬∭∮∯∰∱∲∳∴∵∶∷∽∸∹∺∻∼∾∿≀≁≂≃≄≅≆≇≈≉≊≋≌≍≎≏≐≑≒≓≔≕≖≗≘≙≚≛≜≝≞≟≠≡≢≣≤≥≦≧≨≩≪≫≬≭≮≯≰≱≲≳≴≵≶≷≸≹≺≻≼≽≾≿⊀⊁⊂⊃⊄⊅⊆⊇⊈⊉⊊⊋⊌⊍⊎⊏⊐⊑⊒⊓⊔⊕⊖⊗⊘⊙⊚⊛⊜⊝⊞⊟⊠⊡⊢⊣⊤⊥⊦⊧⊨⊩⊪⊫⊬⊭⊮⊯⊰⊱⊲⊳⊴⊵⊶⊷⊸⊹⊺⊻⊼⊽⊾⊤⊥", 10, 500, 12, RenderHandler::getInstance().textRenderer.getConsoleFont());
        RenderHandler::getInstance().renderText(U"ЀЁЂЃЄЅІЇЈЉЊЋЌЍЎЏАБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдежзийклмнопрстуфхцчшщъыьэюяѐёђѓєѕіїјљњћќѝўџѠѡѢѣѤѥѦѧѨѩѪѫѬѭѮѯѰѱѲѳѴѵѶѷѸѹѺѻѼѽѾѿҀҁ҂҃҄҅҆҇҈҉ҊҋҌҍҎҏҐґҒғҔҕҖҗҘҙҚқҜҝҞҟҠҡҢңҤҥҦҧҨҩҪҫҬҭҮүҰұҲҳҴҵҶҷҸҹҺһҼҽҾҿ", 10, 550, 13, RenderHandler::getInstance().textRenderer.getConsoleFont());
        RenderHandler::getInstance().renderText(U"ԀԁԂԃԄԅԆԇԈԉԊԋԌԍԎԏԐԑԒԓԔԕԖԗԘԙԚԛԜԝԞԟԠԡԢԣԤԥԦԧԨԩԪԫԬԭԮԯ", 10, 600, 22, RenderHandler::getInstance().textRenderer.getConsoleFont());
        RenderHandler::getInstance().renderText(U"ꙀꙁꙂꙃꙄꙅꙆꙇꙈꙉꙊꙋꙌꙍꙎꙏꙐꙑꙒꙓꙔꙕꙖꙗꙘꙙꙚꙛꙜꙝꙞꙟꙠꙡꙢꙣꙤꙥꙦꙧꙨꙩꙪꙫꙬꙭꙮ꙯꙰꙱꙲꙳ꙴꙵꙶꙷꙸꙹꙺꙻ꙼꙽꙾ꙿ", 10, 650, 22, RenderHandler::getInstance().textRenderer.getConsoleFont());
        RenderHandler::getInstance().renderText(U"ᲀᲁᲂᲃᲄᲅᲆᲇᲈᲉ", 10, 700, 22, RenderHandler::getInstance().textRenderer.getConsoleFont());
        RenderHandler::getInstance().renderText(U"̛̀́̂̃̄̅̆̇̈̉̊̋̌̍̎̏̐̑̒̓̔̕̚◌͡", 10, 750, 22, RenderHandler::getInstance().textRenderer.getConsoleFont());
        mainWindow->refresh();

        //log("FPS: " + std::to_string(1.0 / deltaTime));
        lastFrameTime = currentFrameTime;
    }

    log_debug("Shutting down Core...");
}

float Core::getDeltaTime()
{
    return deltaTime;
}
