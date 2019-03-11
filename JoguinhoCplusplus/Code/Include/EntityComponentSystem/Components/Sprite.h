#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "IL/il.h"
#include "Transform.h"

class Sprite : public Component {

private:
    SDL_Renderer* renderer_;
    SDL_Texture* texture_ = nullptr;
    
    Transform* transform_ = nullptr;
    
    std::string path_;
    bool fit_to_image_;

    struct Animation {
        bool animated_;
        int frames_count_;
        int speed_;

        Animation() {
            this->animated_ = false;
            this->frames_count_ = 0;
            this->speed_ = 100;
        }

        Animation(const int& frames, const int& speed, const bool& animated) {
            this->frames_count_ = frames;
            this->speed_ = speed;
            this->animated_ = animated;
        }

    } animation_info_;
public:
    Sprite() = default;

    Sprite(SDL_Renderer* renderer) {
        this->renderer_ = renderer;
    }

    Sprite(SDL_Renderer* renderer, const std::string& imagePath,
           bool fitToImage = false) : Sprite(renderer) {
        this->setTextureFromImage(imagePath);
        this->fit_to_image_ = fitToImage;
    }

    Sprite(SDL_Renderer* renderer, const std::string& imagePath,
           const int& frames, const int& speed,
           const bool& animated) : Sprite(renderer, imagePath) {
        this->animation_info_ = Animation(frames, speed, animated);
    }

    ~Sprite() {
        std::cout << "destrutor do Sprite_component Chamado\n";
        SDL_DestroyTexture(this->texture_);
        if (!this->entity_) {
            delete this->transform_;
        }
    }

    void init() override {
        if (this->entity_) {
            this->transform_ = this->entity_->getComponent<Transform>();
        } else {
            this->transform_ = new Transform();
        }

        if (this->fit_to_image_) {
            this->transform_->setWidth(this->checkWidth(this->path_));
            this->transform_->setHeight(this->checkHeight(this->path_));
        }

        this->transform_->setSrcRect(static_cast<int>(this->transform_->
                                                      getwidth()),
                         static_cast<int>(this->transform_->getHeight()));

        this->transform_->setDestRect(this->transform_->getSrcRect()->w,
                                      this->transform_->getSrcRect()->h);
    }

    void update() override {
        if (this->animation_info_.animated_) {
            int sprite_width = this->transform_->getSrcRect()->w;
            int sprite_speed = SDL_GetTicks() / this->animation_info_.speed_;
            int actual_frame = sprite_speed % this->animation_info_.frames_count_;

            this->transform_->getSrcRect()->x = sprite_width * actual_frame;
        }

        this->transform_->setDestRect(this->transform_->getScale() *
                                      this->transform_->getSrcRect()->w,
                                      this->transform_->getScale() *
                                      this->transform_->getSrcRect()->h,
                                      static_cast<int>(this->transform_->
                                                       getPosition().getX()),
                                      static_cast<int>(this->transform_->
                                                       getPosition().getY()));
    }

    void draw() override {
        SDL_RenderCopy(this->renderer_, this->texture_,
                       this->transform_->getSrcRect(),
                       this->transform_->getDestRect());
    }

    void setTextureFromImage(const std::string& imagePath) {
        this->path_ = imagePath;
        SDL_Surface* surface = IMG_Load(imagePath.c_str());
        if (surface) {
            std::cout << "surface img para " << imagePath << 
                " carregada com sucesso\n";
            this->texture_ = SDL_CreateTextureFromSurface(this->renderer_,
                                                          surface);
            if (this->texture_) {
                std::cout << "textura para " << imagePath <<
                    " criada com sucesso\n";
            }
        }
        SDL_FreeSurface(surface);
    }

    int checkWidth(const std::string& img) {
        ilInit();
        ILuint texId = ilGenImage();

        ilBindImage(texId);

        bool success = ilLoadImage(img.c_str());
        if (!success) {
            return this->transform_->getwidth();
        }

        return static_cast<int>(ilGetInteger(IL_IMAGE_WIDTH));
    }

    int checkHeight(const std::string& img) {
        ilInit();
        ILuint texId = ilGenImage();

        ilBindImage(texId);

        bool success = ilLoadImage(img.c_str());
        if (!success) {
            return this->transform_->getHeight();
        }

        return static_cast<int>(ilGetInteger(IL_IMAGE_HEIGHT));
    }

    Transform* getTransform() {
        return this->transform_;
    }

};